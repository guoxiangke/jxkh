<?php // $Id$

/**
 * @file
 *  Link general private message module functionalities to services module.
 */

/**
 * Get all of a users private messages.
 *
 * @param <int> $uid
 *   A user ID for whom's messages to return.
 *
 * @param <string> $type
 * Which type of messages you would like to retrieve
 * possibilities are inbox or sent.
 *
 * @param <bool> $load_full
 * Boolean. Whether to load the full message for each message or not.
 *
 *  @param $offset
 *   Integer (optional). An offset integer for paging.
 * @param $limit
 *   Integer (optional). A limit integer for paging.
 *
 * @return
 *   An array of messages.
 *
 */
function pm_service_get($uid, $type = 'inbox', $load_full = FALSE, $offset = 0, $limit = 0) {
  $messages = array();
  $pms = array();

  // if no type passed set default type to inbox.
  if (!$type) {
    $type = 'inbox';
  }
  elseif ($type != 'inbox' && $type != 'sent') {
    return services_error(t('Invalid type passed'), 400);
  } 
  // load the user account.
  $account = user_load($uid);
  if (empty($account)) {
    return services_error(t('There is no user with such ID.'), 404);
  }
  else {
    module_load_include('inc', 'privatemsg', 'privatemsg.pages');
    // construct the query and retrieve the correct set of messages.
    $query = _privatemsg_assemble_query('list', $account, $type);
    // handle any paging if an offset or a limit was passed in.
    if (empty($offset) && !empty($limit)) {
      $result = db_query_range($query['query'], 0, $limit);
    } 
    elseif (!empty($offset) && !empty($limit)) {
      $result = db_query_range($query['query'], $offset, $limit);
    }
    elseif (!empty($offset) && empty($limit)) {
      $rows = (int)db_result(db_query($query['count']));
      $result = db_query_range($query['query'], $offset, $rows);
    }
    else {
      // no paging, we are retrieving everything.
      $result = db_query($query['query']);
    }
    // loop the result object to get the messages.
    while ($row = db_fetch_object($result)) {
      $pms[$row->thread_id] = $row;
    }
    // check whether we are loading the full message or not.
    if (!empty($pms) && $load_full) {
      foreach ($pms as $thread_id => $msg) {
        $messages[] = privatemsg_thread_load($thread_id, $account, NULL, FALSE);
      }
    }
    else {
      $messages = $pms;
    }
  }
  // return messages.
  return $messages;
}

/**
 * Get the number of unread private messages for a specific user.
 * @param <int> $uid
 *   A user UID to get the number of unread messages for.
 *
 * @return
 *   The unread count.
 */
function pm_service_unread_count($uid) {
  $account = user_load($uid);
  if (empty($account)) {
    return services_error(t('There is no user with such ID.'), 404);
  }
  else {
    $result = privatemsg_unread_count($account);
  }
  // return unread count.
  return $result;
}

/**
 * Send a private message to one or more recipients.
 * @param <int> $author
 * The User ID for the author of the message.
 *
 * @param <string> $recipients
 * A comma separated list of usernames for recipients of the message.
 *
 * @param <string> $subject
 * A message subject
 *
 * @param <string> $body
 * A message body
 *
 * @param <int> $thread_id
 * A thread ID. pass this parameter if you are sending a message reply.
 *
 * @return <bool>
 * Return TRUE if sending the message was successful.
 */
function pm_service_send($author, $recipients, $subject, $body = '', $thread_id = NULL) {
  module_load_include('inc', 'privatemsg', 'privatemsg.pages');
  $form_state = array();
  // validate the message author actually exists + is not anonymous user.
  $account = user_load($author);
  if (empty($account) || $account->uid == 0) {
    return services_error(t('There is no user with such ID.'), 404);
  }
  // validate at least 1 recipient has been passed in.
  if ($recipients == '' && !$thread_id) {
    return services_error(t('There are no recipients, please enter a recipient for the message.'), 400);
  }
  elseif (!$thread_id) {
    // no thread ID - we are sending a new message.
    // convert the recipients string to an array of user objects.
    list($recipients, $invalid) = _privatemsg_parse_userstring($recipients);
    $result = privatemsg_new_thread($recipients, $subject, $body, array('author' => $account));
    if ($result['success']) {
      return TRUE;
    }
    else {
      return services_error(implode("\n", $result['messages']['error']), 400);
    }
  }
  else {
    // there is a thread id so we are sending a reply.
    $result = privatemsg_reply($thread_id, $body, array('author' => $account));
    if ($result['success']) {
      return TRUE;
    }
    elseif (!empty($result[0])) {
      // if $result[0] this means the thread could not be loaded.
      return services_error($result[0], 404);
    }
    else {
      // else there was some other problem.
      return services_error(implode("\n", $result['messages']['error']), 400);
    }
  }
}



<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function center_message_alter($centerid, $fun, $data) {
  global $user;
  if ($user->uid == 0) {
    return services_error('reject access', 406);
  }
  if ($fun) {
    if (is_numeric($fun)) {
      $data['nid'] = $fun;
    } else {
      //return call_user_func('center_question_' . $fun, $centerid, $data);
    }
  }
  if (!$center = sbq_center_load($centerid)) {
    return services_error('not found the center form ' . $centerid, '404');
  }
  
  if ($mid = center_message_get_privatemsgid($centerid)) {
    $result = privatemsg_reply($mid, $data['body'], array( 'author' => $user ));
  } else {
    $recipients = user_load($center->uid);
    list($recipients, $invalid) = _privatemsg_parse_userstring($recipients->name);
    $result = privatemsg_new_thread($recipients, 'center|' . $centerid . '|' . $user->uid, $data['body'], array( 'author' => $user ));
  }
  if (isset($result['success']) && $result['success']) {
    return array(
        'mid' => $result['message']->mid,
//    'author' => $result['message']->author->uid,
//    'recipients' => $resul['message']->recipients->uid,
        'centermid' => $result['message']->thread_id
    );
  }
  return $result;
}

/**
 * query center message 
 * @param type $centerid
 * @param type $fun
 * @param type $page
 * @param type $fields
 * @param type $parameters
 * @param type $pagesize
 */
function center_message_query($centerid, $fun = NULL, $page, $fields, $parameters, $pagesize) {
  if (!$centermid = center_message_get_privatemsgid($centerid)) {
    return array();
  }

  if (isset($parameters['start'])) {
    $result = privatemsg_thread_load($centermid, NULL, $parameters['start']);
  } else {
    $result = privatemsg_thread_load($centermid);
  }
  $message = array();
  $user_img = array();
  foreach ($result['messages'] as $key => $value) {
    if (!isset($user_img[$value->author->uid])) {
      $user_img[$value->author->uid] = array(
          'uid' => $value->author->uid,
          'user_avart' => isset($value->author) ? file_create_url($value->author) : NULL,
          'name' => $value->author->name,
      );
    }
    $message[] = array(
        'mid' => $value->mid,
        'body' => $value->body,
        'timestamp' => $value->timestamp ,
        'is_new' => $value->is_new,
        'author' => $user_img[$value->author->uid],
        // 'recipients' => $user_img[$value->user->uid]
    );
  }
  return array(
      'centermid' => $result['thread_id'],
      'to' => $result['to'],
      'from' => $result['from'],
      'start' => $result['start'],
      'count' => $result['message_count'],
      'message' => $message
  );
}

/**
 * get center private mid
 * @param type $centerid 
 * @param type $user
 */
function center_message_get_privatemsgid($centerid, $account = NULL) {
  if (!$account) {
    global $user;
    $account = $user;
  }

  $result = db_select('pm_message', 'pm')
      ->fields('pm', array( 'mid' ))
      ->condition('subject', 'center|' . $centerid . '|' . $account->uid)
      ->orderBy('timestamp', 'ASC')
      ->range(0, 1)
      ->execute()
      ->fetchCol();

  return reset($result);
}

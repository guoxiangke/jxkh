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
      return call_user_func('center_question_' . $fun, $centerid, $data);
    }
  }
  if (!$center = sbq_center_get_center($centerid)) {
    return services_error('not found the center form ' . $centerid, '404');
  }
  if ($mid = center_message_get_privatemsgid()) {
    $result = privatemsg_reply($mid['mid'], $data['body'], array( 'author' => $user ));
  } else {
    $recipients = user_load($center->uid);
    list($recipients, $invalid) = _privatemsg_parse_userstring($recipients->name);
    $result = privatemsg_new_thread($recipients, 'center|' . $centerid . '|' . $user->uid, $data['body'], array( 'author' => $user ));
  }
  return $result;
}

/**
 * get center private mid
 * @param type $centerid 
 * @param type $user
 */
function center_message_get_privatemsgid($centerid, $account = NULL) {
  if (!$user) {
    global $user;
    $account = $user;
  }
  $result = db_select('pm_message', 'pm')
      ->fields('pm', array( 'mid' ))
      ->condition('subject', 'center|' . $centerid . '|' . $user->uid)
      ->orderBy('timestamp', 'DESC')
      ->range(1)
      ->execute()
      ->fetchField();

  return $result;
}

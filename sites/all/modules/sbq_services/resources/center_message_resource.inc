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

  $message = array(
      'author' => $user,
  );
  if (isset($data['image_fid'])) {
    $message['field_message_image']['und'][0]['fid'] = $data['image_fid'];
  }
  if ($data['video_fid']) {
    $message['field_message_video']['und'][0]['fid'] = $data['video_fid'];
  }
  if ($mid = center_message_get_privatemsgid($center->uid) && false) {
    $message['thread_id'] = $mid;
    $result = privatemsg_reply($mid, $data['body'], $message);
  } else {
    $recipients = user_load($center->uid);
    list($recipients, $invalid) = _privatemsg_parse_userstring($recipients->name);
    $result = privatemsg_new_thread($recipients, 'center|' . $centerid . '|' . $user->uid, $data['body'], $message);
  }
  if (isset($result['success']) && $result['success']) {
    return array(
        'mid' => $result['message']->mid,
        'centermid' => $result['message']->thread_id
    );
  }
  return $result['error'];
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
  if (!$center = sbq_center_load($centerid)) {
    return services_error('not found the center form ' . $centerid, '404');
  }
  if (!$centermid = center_message_get_privatemsgid($center->uid)) {
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
    if (!empty($value->field_message_image)) {
      $image = file_create_url($value->field_message_image['und'][0]['uri']);
    }
//    if (!empty($value->field_message_video)) {
//      $video = file_create_url($value->field_message_video['und'][0]['uri']);
//    }
    $message[] = array(
        'mid' => $value->mid,
        'body' => $value->body,
        'timestamp' => $value->timestamp,
        'is_new' => $value->is_new,
        'author' => $user_img[$value->author->uid],
        'image' => isset($image) ? $image : '',
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
function center_message_get_privatemsgid($center_user_id, $account = NULL) {
  if (!$account) {
    global $user;
    $account = $user;
  }
  $query = 'select r.mid from pm_index r '
      . 'inner join pm_index p on r.thread_id = p.thread_id '
      . 'where p.recipient = :user_id and r.recipient =  :center_user_id '
      . 'order by mid asc limit 1';
  $mids = db_query($query, array( ':user_id' => $account->uid, ':center_user_id' => $center_user_id ))->fetchCol('r.mid');
  return reset($mids);
}

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
  if (isset($data['video_fid'])) {
    $message['field_message_video']['und'][0]['fid'] = $data['video_fid'];
    $message['field_message_video']['und'][0]['display'] = 1;
  }
  if (isset($data['voice_fid'])) {
    $message['field_message_voice']['und'][0]['fid'] = $data['voice_fid'];
    $message['field_message_voice']['und'][0]['display'] = 1;
  }

  if ($mid = center_message_get_privatemsgid($center->uid)) {
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

  if ($fun) {
    if (!is_numeric($fun)) {
      $function = 'center_message_' . $fun;
      if (!function_exists($function)) {
        services_error("not found $fun interface", 404);
      }
      return $function($centerid, $mid, $page, $fields, $parameters, $pagesize);
    } else {
      return 'error : not found this interface';
    }
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

    $data = array(
        'mid' => $value->mid,
        'body' => $value->body,
        'timestamp' => $value->timestamp,
        'is_new' => $value->is_new,
        'author' => $user_img[$value->author->uid],
    );
   
    if (!empty($value->field_message_image)) {
      $data['image'] = file_create_url($value->field_message_image['und'][0]['uri']);
    }
    if (!empty($value->field_message_video)) {
      $data['video'] = file_create_url($value->field_message_video['und'][0]['uri']);
    }
    if (!empty($value->field_message_voice)) {
      $data['voice'] = file_create_url($value->field_message_voice['und'][0]['uri']);
    }
    $message[] = $data;
//    if (!empty($value->field_message_video)) {
//      $video = file_create_url($value->field_message_video['und'][0]['uri']);
//    }
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

function center_message_new($centerid, $mid, $page, $fields, $parameters, $pagesize) {
  $message_new_count = db_select('pm_index', 'pmi')
      ->fields('pmi', array( 'mid' ))
      ->condition('is_new', 1)
      ->condition('recipient', $user->uid)
      ->condition('thread_id', center_message_get_privatemsgid($center->uid))
      ->condition('deleted', 0)
      ->execute()
      ->rowCount();

  //预约门诊
  module_load_include('inc', 'sbq_services', 'resources/center_reservation_resource');
  $messages = center_reservation_message($centerid, $user->uid);
}

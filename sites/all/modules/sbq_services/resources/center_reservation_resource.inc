<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * alter control
 * @param type $centerid
 * @param type $fun
 * @param type $data
 * @return type
 */
function center_reservation_alter($centerid, $fun, $data) {
  if ($fun) {
    if (is_numeric($fun)) {
      
    } else {
      
    }
  }
  if (!$center = sbq_center_load($centerid)) {
    services_error("the center id $centerid not found", 401);
  }
  $data['centerid'] = "center ({$centerid})";
  $nodes = _center_reservation_format($data);
  $node = reset($nodes);
  return _node_resource_create($node);
}

/**
 * query control
 * @param type $centerid
 * @param type $fun
 * @param type $uid
 * @param type $page
 * @param type $fields
 * @param type $parameters
 * @param type $pagesize
 * @return type
 */
function center_reservation_query($centerid, $fun = NULL, $uid, $page, $fields, $parameters, $pagesize) {
  global $user;
  if ($fun) {
    if (!is_numeric($fun)) {
      $function = 'center_reservation_' . $fun;
      if (!function_exists($function)) {
        services_error("no found $fun resources", 404);
      }
      return $function($centerid, $user->uid, $page, $fields, $parameters, $pagesize);
    } else {
      $data = sbq_center_reservation_get_reservation($uid->uid, $fun);
      return reset(_center_reservation_format($data, 'data'));
    }
  }
  //$uid = isset($parameters['uid']) ? $parameters['uid'] : $uid->uid;

  $data = sbq_center_reservation_get_reservation($user->uid, null, array( 'targetid' => $centerid, 'page' => array( 'page' => $page, 'pagesize' => $pagesize ) ));

  $nodes['reservation'] = _center_reservation_format($data, 'data', TRUE);
  return $nodes;
}

/**
 * convert data between 
 * @param type $data
 * @param type $type
 * @param type $is_list
 * @return string
 */
function _center_reservation_format($data, $type = 'node', $is_list = FALSE) {
  if (!$is_list) {
    $data = array( $data );
  }
  $nodes = array();
  foreach ($data as $key => $value) {
    $value = (array) $value;
    if ($type == 'node') {
      $node['type'] = SBQ_CENTER_RESERVATION_NODE_TYPE;
      $node['body']['und'][0]['value'] = $value['body'];
      $node['field_real_name']['und'][0]['value'] = $value['name'];

      $node['field_sex']['en']['value'][0] = '0'; //$value['sex'];
      $node['field_age']['und'][0]['value'] = $value['age'];
      $node['field_identity']['und'][0]['value'] = $value['identity'];
      $node['field_case_num']['und'][0]['value'] = $value['case_num'];
      $node['field_phone']['und'][0]['value'] = $value['phone'];
      $node['og_group_ref']['und'][0]['target_id'] = $value['centerid'];
      //pop-up
      $node['field_reservation_time']['und'][0]['value']['date'] = date('Y-m-d', $value['reservation_time']);
      // $node['field_reservation_time']['und'][0]['value']['time'] = date('H:i', $value['reservation_time']);
      $node['field_reservation_time']['und'][0]['value']['time'] = '11:00';
      // $node['field_reservation_time']['und'][0]['value']['date'] = date('Y-m-d', $value['reservation_time']);
    } else {
      $node['nid'] = (int) $value['nid'];
      $node['body'] = $value['body']['und'][0]['value'];
      $node['name'] = $value['field_real_name']['und'][0]['value'];
      $node['sex'] = $value['field_sex']['und'][0]['value'];
      $node['age'] = $value['field_age']['und'][0]['value'];
      $node['identity'] = $value['field_identity']['und'][0]['value'];
      $node['case_num'] = $value['field_case_num']['und'][0]['value'];
      $node['phone'] = $value['field_phone']['und'][0]['value'];
      $node['status'] = $value['field_reservation_status']['und'][0]['value'];
      $date = new DateTime($value['field_reservation_time']['und'][0]['value']);
      $node['reservation_time'] = $date->getTimestamp();
    }

    $nodes[] = $node;
  }
  return $nodes;
}

/**
 * 
 * @param type $centerid
 * @param type $userid
 * @return string
 */
function center_reservation_message($centerid, $userid) {
  //$reservation_node = sbq_center_reservation_fetch_by_center($centerid);
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'message')
      ->propertyCondition('type', 'sbq_center_reservation_accept')
      ->propertyOrderBy('timestamp', 'DESC')
      ->propertyCondition('uid', $userid)
      ->fieldCondition('field_node_ref', 'target_id', $centerid);
  if ($time = variable_get('reservation_last_watch_' . $userid . '_' . $centerid)) {
    //$query->propertyCondition('timestamp', $time, '>');
  }
  $result = $query->execute();
  if (!$result['message']) {
    return '';
  }
  $mesage = array();
  foreach (message_load_multiple(array_keys($result['message'])) as $key => $value) {
    $m = (array) $value->buildContent();
    $text = strip_tags($m['message__message_text__0']['#markup']);
    $key = $value->arguments['!center_reservation_id'];
    //$key = $m['field_center_reservation_send']['#object']->field_node_ref['und'][0]['target_id'];
    $message[] = array( 'nid' => $key, 'text' => $text );
  }
  variable_set('reservation_last_watch_' . $userid . '_' . $centerid, time());
  return $message;
}

/**
 * get one month can reservation date
 * @param type $centerid
 * @param type $uid
 * @param type $page
 * @param type $fields
 * @param type $parameters
 * @param type $pagesize
 * @return type
 */
function center_reservation_fetch($centerid, $uid, $page, $fields, $parameters, $pagesize) {
  $month = $parameters['month'];
  if (is_null($month)) {
    $month = array( date('m') );
  }
  $cur_month = date('m');
  $year = date('Y');
  $now_day = date('d');
  foreach ($month as $key => $value) {
    $start = 1;
    if ((int) $cur_month === (int) $value) {
      $start = $now_day;
    }
    $days = cal_days_in_month(CAL_GREGORIAN, $value, $year);
    for ($i = $start; $i <= $days; $i++) {
      $date = "$year-$value-$i";
      //  return $date;
      $dateTime = new DateTime($date);
      if (sbq_center_reservation_can_reservation($date, $centerid, TRUE)) {
        $data[] = array(
            $dateTime->getTimestamp() => array(
                'a' => TRUE, 'p' => TRUE
            )
        );
      }
    }
  }
  return isset($data) ? $data : array();
}

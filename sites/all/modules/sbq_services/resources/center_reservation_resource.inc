<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * 
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
  $nodes = _center_reservation_format($data);
  $node = reset($nodes);
  return _node_resource_create($node);
}

function center_reservation_query($centerid, $fun = NULL, $uid, $page, $fields, $parameters, $pagesize) {
  if ($fun) {
    if (is_numeric($fun)) {
      
    } else {
      $function = 'center_reservation_' . $fun;
      if (!function_exists($function)) {
        services_error("no found $fun resources", 404);
      }
      return $function($centerid, $uid, $page, $fields, $parameters, $pagesize);
    }
  }
  $uid = isset($parameters['uid']) ? $parameters['uid'] : NULL;
  $nodes = sbq_center_reservation_get_submissions(array( 'uid' => $uid, 'nid' => $reservation_node->nid ), $page, $pagesize);
  $nodes['reservation'] = _center_reservation_format($nodes['reservation'], 'data', TRUE);
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
    if ($type == 'node') {
      $node['type'] = SBQ_CENTER_RESERVATION_NODE_TYPE;
      $node['body']['und'][0]['value'] = $value['body'];
      $node['field_real_name']['und'][0]['value'] = $value['name'];
      $node['field_sex']['und'][0]['value'] = 1;//$value['sex'];
      $node['field_age']['und'][0]['value'] = $value['age'];
      $node['field_identity']['und'][0]['value'] = $value['identity'];
      $node['field_case_num']['und'][0]['value'] = $value['case_num'];
      $node['field_phone']['und'][0]['value'] = $value['phone'];
      $node['field_node_ref']['und'][0]['target_id'] = $value['centerid'];
      $node['field_reservation_time']['und'][0]['value'] = date('Y-m-d', $value['reservation_time']);
    } else {
      $node['body'] = $value['body']['und'][0]['value'];
      $node['name'] = $value['field_real_name']['und'][0]['value'];
      $node['sex'] = $value['field_sex']['und'][0]['value'];
      $node['age'] = $value['field_age']['und'][0]['value'];
      $node['identity'] = $value['field_identity']['und'][0]['value'];
      $node['case_num'] = $value['field_case_num']['und'][0]['value'];
      $node['phone'] = $value['field_phone']['und'][0]['value'];
      $node['centerid'] = $value['field_node_ref']['und'][0]['target_id'];
      $node['reservation_time'] = $value['field_reservation_time']['und'][0]['value'];
    }

    $nodes[] = $node;
  }
  return $nodes;
}

function center_reservation_message($centerid, $userid) {
  $reservation_node = sbq_center_reservation_node_by_center($centerid);
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'message')
      ->propertyCondition('type', 'sbq_center_reservation_accept')
      ->propertyOrderBy('timestamp', 'DESC')
      ->fieldCondition('field_node_ref ', 'target_id', $reservation_node->nid);
  if ($time = variable_get('reservation_last_watch_' . $userid . '_' . $centerid)) {
    $query->propertyCondition('timestamp', $time, '>');
  }
  $result = $query->execute();

  if (!$result['message']) {
    //  $mids = array_keys($result['message']);
    return '';
  }
  $mesage = array();
  foreach (message_load_multiple(array_keys($result['message'])) as $key => $value) {
    $m = $value->buildContent();
    $message[] = strip_tags($m['message__message_text__0']['#markup']);
  }
  // variable_set('reservation_last_watch_' . $userid . '_' . $centerid, time());
  return $message;
}

function center_reservation_fetch($centerid, $uid, $page, $fields, $parameters, $pagesize) {
  $month = $parameters['month'];
  if (is_null($month)) {
    $month = date('m');
  }
  $year = date('Y');
  $now_day = date('d');
  $days = cal_days_in_month(CAL_GREGORIAN, $month, $year);

  for ($i = $now_day; $i <= $days; $i++) {
    $date = "$year-$month-$i";

    if (sbq_center_reservation_can_reservation($date, $centerid)) {
      $data[] = array(
          $date => array(
              'a', 'p'
          )
      );
    }
  }
  return isset($data) ? $data : array();
}

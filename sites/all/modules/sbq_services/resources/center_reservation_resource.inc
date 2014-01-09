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
  $center_node = sbq_center_reservation_node_by_center($centerid);
  module_load_include('inc', 'webform_service', 'webform_service');
  $submission = _center_reservation_format($data);
  $result = reset($submission);
  return _submission_resource_create($center_node->nid, $result);
}

function center_reservation_query($centerid, $fun = NULL, $uid, $page, $fields, $parameters, $pagesize) {
  $reservation_node = sbq_center_reservation_node_by_center($centerid);
  module_load_include('inc', 'webform', 'includes/webform.submissions');
  if ($fun) {
    if (is_numeric($fun)) {
      $webform = webform_get_submission($reservation_node->nid, $fun);
      $nodes = _center_reservation_format($webform, 'data');
      return reset($nodes);
    } else {
      
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
function _center_reservation_format($data, $type = 'webform', $is_list = FALSE) {
  if (!$is_list) {
    $data = array( $data );
  }
  $nodes = array();
  foreach ($data as $key => $value) {
    if ($type == 'webform') {
      $node[1][0] = $value['is_outpatient'];
      $node[2] = $value['name'];
      $node[3] = $value['sex'];
      $node[4] = date('Y-m-d H:i:s', $value['bron']);
      $node[5] = date('Y-m-d H:i:s', $value['reservation_time']);
      $node[6] = $value['body'];
      $node[7] = $value['file'];
      $node[8] = $value['recommended'];
      // $node[9] = $value['centerid'];
      $node[10] = $value['category'];
//      $node['values']['submitted_tree']['sbq_center_outpatient'][0] = '';
//      $node['values']['submitted_tree']['sbq_center_name'] = '';
//      $node['values']['submitted_tree']['sbq_center_sex'] = '';
//      $node['values']['submitted_tree']['sbq_center_bron'] = '';
//      $node['values']['submitted_tree']['sbq_center_time'] = '';
//      $node['values']['submitted_tree']['sbq_center_body'] = '';
//      $node['values']['submitted_tree']['sbq_center_file'] = '';
//      $node['values']['submitted_tree']['sbq_center_recommended'] = '';
//      $node['values']['submitted_tree']['sbq_center_id'] = '';
//      $node['values']['submitted_tree']['sbq_center_formcategory'] = '';
    } else {
      $origin = $value;
      $value = $value->data;
      $node['is_outpatient'] = $value[1]['value'][0];
      $node['name'] = $value[2]['value'][0];
      $node['sex'] = $value[3]['value'][0];
      $bron = new DateTime($value[4]['value'][0]);
      $node['bron'] = $bron->getTimestamp();
      $reservation = new DateTime($value[5]['value'][0]);
      $node['reservation_time'] = $reservation->getTimestamp();
      $node['body'] = $value[6]['value'][0];
      $node['file'] = $value[7]['value'][0];
      $node['recommended'] = $value[8]['value'][0];
      $node['category'] = $value[10]['value'][0];
      $node['uid'] = $origin->uid;
      $node['sid'] = $origin->sid;
      $node['status'] = $value[11]['value'][0];
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
  
  if (!isset($result['message'])) {
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


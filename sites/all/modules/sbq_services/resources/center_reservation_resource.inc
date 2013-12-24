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

  $data['centerid'] = $centerid;
  if ($fun) {
    if (is_numeric($fun)) {
      //$data[''] = $
    } else {
      
    }
  }
  
  module_load_include('inc', 'webform_service', 'webform_service');
  $submission = _center_reservation_format($data);
  //return $submission;
  $result = reset($submission);
  return _submission_resource_create(SBQ_CENTER_RESERVATION_NODE_ID, $result);
}
function center_reservation_query($centerid, $fun = NULL, $uid, $page, $fields, $parameters, $pagesize){
//  webform_get_submissions($filters);
//  webform_get_submissions($filters);
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
      $node[3] = $value['sex'] ;
      $node[4] = date('Y-m-d H:i:s', $value['bron']);
      $node[5] = date('Y-m-d H:i:s', $value['reservation_time']);
      $node[6] = $value['body'];
      $node[7] = $value['file'];
      $node[8] = $value['recommended'];
      $node[9] = $value['centerid'];
      $node[10] = $value['category'] ;
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
      
    }
    $nodes[] = $node;
  }
  return $nodes;
}

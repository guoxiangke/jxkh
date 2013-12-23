<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
          
function center_reservation_resource_definition() {
  module_load_include('inc', 'services', 'resources/node_resource');
  module_load_include('inc', 'webform', 'webform_service');
  $definition['center']['targeted_actions']['reservation'] = array(
      'help' => 'create center reservation',
      'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/center_reservation_resource' ),
      'callback' => 'center_reservation_alter',
      'args' => array(
          array(
              'name' => 'centerid',
              'optional' => FALSE,
              'source' => array( 'path' => 0 ),
              'type' => 'int',
              'description' => 'The nid of the submission node',
          ),
          array(
              'name' => 'fun',
              'optional' => TRUE,
              'source' => array( 'path' => 2 ),
              'default value' => '',
              'type' => 'int',
              'description' => 'alter center question function',
          ),
          array(
              'name' => 'reservation',
              'optional' => FALSE,
              'source' => 'data',
              'description' => 'The submission data to create',
              'type' => 'array',
          ),
      ),
      'access callback' => '_submission_resource_access',
      'access arguments' => array( 'create' ),
      'access arguments append' => TRUE,
  );

  return $definition;
}

function center_reservation_alter($centerid, $fun, $data) {return 'ss';
  if ($fun) {
    if (is_numeric($fun)) {
      //$data[''] = $
    } else {
      
    }
  }
  $submission = _center_reservation_format($data);
  _submission_resource_create($webfornid, $submission);
  return 'center reservation alter';
}

function _center_reservation_format($data, $type = 'webform', $is_list = FALSE) {
  if (!$is_list) {
    $data = array( $data );
  }

  $nodes = array();

  foreach ($data as $key => $value) {
    if ($type == 'webform') {
      $node[1][0] = '1';
      $node[2] = 'qqq';
      $node[3] = '0';
      $node[4] = '2013-12-04';
      $node[5] = '2013-12-25';
      $node[6] = 'qqqq';
      $node[7] = '4148';
      $node[8] = 'checahh';
      $node[9] = '21713';
      $node[10] = '1';
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
  }

  return $nodes;
}

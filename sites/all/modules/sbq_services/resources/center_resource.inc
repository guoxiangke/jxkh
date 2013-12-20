<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function center_resource_definition() {
  module_load_include('inc', 'services', 'resources/node_resource');
  $definition['center']['operations'] = array(
  );

  $definition['center']['targeted_actions']['question'] = array(
      'help' => 'create center question',
      'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/center_resource' ),
      'callback' => 'center_question_alter',
      'access callback' => '_node_resource_access',
      'access arguments' => array( 'update' ),
      'access arguments append' => TRUE,
      'args' => array(
          array(
              'name' => 'centerid',
              'optional' => FALSE,
              'source' => array( 'path' => 0 ),
              'type' => 'int',
              'description' => 'The center id',
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
              'name' => 'data',
              'optional' => FALSE,
              'source' => 'data',
              'description' => 'The center question',
              'type' => 'array',
          ),
      ),
  );
  $definition['center']['relationships']['question'] = array(
      'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/center_resource' ),
      'help' => 'This method returns center question.',
      'callback' => 'center_question_query',
      'args' => array(
          array(
              'name' => 'centerid',
              'type' => 'int',
              'description' => t('The center id .'),
              'source' => array( 'path' => 0 ),
              'optional' => FALSE,
          ),
          array(
              'name' => 'fun',
              'type' => 'int',
              'description' => t('The function .'),
              'source' => array( 'path' => 2 ),
              'default value' => '',
              'optional' => TRUE,
          ),
          array(
              'name' => 'page',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'The zero-based index of the page to get, defaults to 0.',
              'default value' => 0,
              'source' => array( 'param' => 'page' ),
          ),
          array(
              'name' => 'fields',
              'optional' => TRUE,
              'type' => 'string',
              'description' => 'The fields to get.',
              'default value' => '*',
              'source' => array( 'param' => 'fields' ),
          ),
          array(
              'name' => 'parameters',
              'optional' => TRUE,
              'type' => 'array',
              'description' => 'Parameters array',
              'default value' => array(),
              'source' => array( 'param' => 'parameters' ),
          ),
          array(
              'name' => 'pagesize',
              'optional' => TRUE,
              'type' => 'int',
              'description' => 'The zero-based index of the page to get, defaults to 0.',
              'default value' => variable_get('services_node_index_page_size', 10),
              'source' => array( 'param' => 'pagesize' ),
          ),
      ),
      'access callback' => '_node_resource_access',
      'access arguments' => array( 'view' ),
      'access arguments append' => TRUE,
  );


  return $definition;
}

function center_question_alter($centerid, $questionid, $fun, $data) {
  if ($fun) {
    if (is_numeric($fun)) {
      $data['nid'] = $fun;
    } else {
      return call_user_func('center_question' . $fun, $centerid, $data);
    }
  }
  $node = _center_question_format($data);
  $node = _node_resource_create($node);
  return $node;
}

function center_question_query($centerid, $fun = NULL, $page, $fields, $parameters, $pagesize) {
  if ($fun) {
    if (is_numeric($fun)) {
      $parameters['nid'] = $fun;
    } else {
      return call_user_func('center_question' . $fun, $page, $fields, $pagesize, $parameters, $centerid);
    }
  }
  $data = _center_question_query($fields, $parameters, $page, $pagesize, $centerid);

  if (isset($parameters['nid'])) {
    return reset($data['data']);
  }
  return $data;
}

function _center_question_query($fields = "*", $parameters = array(), $page = 0, $pagesize = 10, $centerid) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'question')
      ->fieldCondition('og_group_ref', 'target_id', $centerid, '=');
  $node_query = clone $query;
  foreach ($parameters as $key => $value) {
    $query->propertyCondition($key, $value);
  }
  $query_result = $query->execute();
  $count = isset($query_result['node']) ? count($query_result['node']) : 0;

  $result = $node_query
      ->propertyOrderBy('created', 'DESC')
      ->range($page * $pagesize, $pagesize)
      ->execute();
  $nids = array();
  if (isset($result['node'])) {
    $nids = array_keys($result['node']);
  }
  $nodes = node_load_multiple($nids);
  $data = array(
      'data' => $nodes,
      'page' => $page,
      'pagecount' => ceil($count / $pagesize),
  );
  return $data;
}

function _center_question_format($data, $target = 'node') {
  if ($target == 'node') {
    $node['title'] = $data['title'];
    $node['type'] = 'question';
    $node['body']['und'][0]['value'] = $data['body'];
    $node['og_group_ref']['und'][0]['target_id'] = $data['centerid'];
    $node['field_tags']['und'] = '中心问答';
    $node['type'] = 'question';
  } else {
    
  }

  return $node;
}

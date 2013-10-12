<?php

function grow_records_resource_definition() {
  module_load_include('inc', 'services', 'resources/node_resource');
  $definition['grow_records']['operations'] = array(
      'retrieve' => array(
          'help' => 'records a user',
          'callback' => '_retrieve',
          'file' => array('type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/grow_records_resource'),
          'access callback' => '_node_resource_access',
          'access arguments' => array('view'),
          'access arguments append' => TRUE,
          'args' => array(
              array(
                  'name' => 'id',
                  'type' => 'int',
                  'description' => 'grow records id.',
                  'source' => array('path' => 0),
                  'optional' => FALSE,
              ),
          ),
      ),
      'create' => array(
          'help' => 'Create a grow records node',
          'file' => array('type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/grow_records_resource'),
          'callback' => '_create',
          'args' => array(
              array(
                  'name' => 'node',
                  'optional' => FALSE,
                  'source' => 'data',
                  'description' => 'grow records node',
                  'type' => 'array',
              ),
          ),
          'access callback' => '_node_resource_access',
          'access arguments' => array('create', array(array('type' => 'grow_records'))),
          'access arguments append' => FALSE,
      ),
      'index' => array(
          'help' => 'List all nodes',
          'file' => array('type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/grow_records_resource'),
          'callback' => '_index',
          'args' => array(
              array(
                  'name' => 'page',
                  'optional' => TRUE,
                  'type' => 'int',
                  'description' => 'The zero-based index of the page to get, defaults to 0.',
                  'default value' => 0,
                  'source' => array('param' => 'page'),
              ),
              array(
                  'name' => 'fields',
                  'optional' => TRUE,
                  'type' => 'string',
                  'description' => 'The fields to get.',
                  'default value' => '*',
                  'source' => array('param' => 'fields'),
              ),
              array(
                  'name' => 'parameters',
                  'optional' => TRUE,
                  'type' => 'array',
                  'description' => 'Parameters array',
                  'default value' => array(),
                  'source' => array('param' => 'parameters'),
              ),
              array(
                  'name' => 'pagesize',
                  'optional' => TRUE,
                  'type' => 'int',
                  'description' => 'Number of records to get per page.',
                  'default value' => variable_get('services_node_index_page_size', 20),
                  'source' => array('param' => 'pagesize'),
              ),
          ),
          'access arguments' => array('access content'),
      ),
  );


  return $definition;
}

function _create($node) {
  $node = array(
      'type' => 'grow_records',
      'title' => $node['title'],
      'field_grow_records_file' => array(
          'und' => array(
              array('fid' => $node['fid'])
          ),
      ),
      'field_grow_records_created' => array(
          'und' => array(
              array(
                  'value' => $node['created']
              )
          )
      ),
  );
  $data = _node_resource_create($node);
  if ($data) {
    
    $data = _grow_records_format(node_load($data['nid']));
  }
  return $data;
}

function _retrieve($nid) {
  return _grow_records_format(_node_resource_retrieve($nid));
}

function _index($page, $fields, $parameters, $page_size) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
          ->propertyCondition('status', 1)
          ->propertyCondition('type', 'grow_records');
  if ($parameters['uid']) {
    $query->propertyCondition('uid', $parameters['uid']);
  }
 // return $parameters;
  if ($parameters['created']) {
    if (is_array($parameters['created'])) {
      $query->fieldCondition('field_grow_records_created', 'value', $parameters['created'][0], '>');
      $query->fieldCondition('field_grow_records_created', 'value', $parameters['created'][1], '<');
    } else {
      $query->fieldCondition('field_grow_records_created', 'value', $parameters['created'], '=');
    }
  }
  $fiter_query = $query;
  $result = $query->execute();
  $count = isset($result['node']) ? count($result['node']) : 0;
  $result = $fiter_query->range($page * $page_size, $page_size)->execute();
  if (isset($result['node'])) {
    $ids = array_keys($result['node']);
    $data['charts'] = _grow_records_format(node_load_multiple($ids));
  }
  $data['count'] = ceil($count / $page_size);
  $data['index'] = $page;
  return $data;
}

function _grow_records_format($data) {
  if (!$data || empty($data)) {
    return array();
  }
  if (!is_array($data)) {
    $data = array($data);
  }
  $format_data = array();
  foreach ($data as $node) {
    $format_data[] = array(
        'id' => $node->nid,
        'title' => $node->title,
        'date' => $node->field_grow_records_created[LANGUAGE_NONE][0]['value'],
        'path' => file_create_url($node->field_grow_records_file[LANGUAGE_NONE][0]['uri']),
        'size' => $node->field_grow_records_file[LANGUAGE_NONE][0]['filesize'],
        'md5' => ''
    );
  }
  return $format_data;
}

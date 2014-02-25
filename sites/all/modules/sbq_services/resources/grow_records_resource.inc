<?php

function grow_records_resource_definition() {
  module_load_include('inc', 'services', 'resources/node_resource');
  $definition['grow_records']['operations'] = array(
      'retrieve' => array(
          'help' => 'records a user',
          'callback' => '_retrieve',
          'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/grow_records_resource' ),
          'access callback' => '_node_resource_access',
          'access arguments' => array( 'view' ),
          'access arguments append' => TRUE,
          'args' => array(
              array(
                  'name' => 'id',
                  'type' => 'int',
                  'description' => 'grow records id.',
                  'source' => array( 'path' => 0 ),
                  'optional' => FALSE,
              ),
          ),
      ),
      'create' => array(
          'help' => 'Create a grow records node',
          'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/grow_records_resource' ),
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
          'access arguments' => array( 'create', array( array( 'type' => 'grow_records' ) ) ),
          'access arguments append' => FALSE,
      ),
      'update' => array(
          'help' => 'Update a node',
          'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/grow_records_resource' ),
          'callback' => '_update',
          'args' => array(
              array(
                  'name' => 'nid',
                  'optional' => FALSE,
                  'source' => array( 'path' => 0 ),
                  'type' => 'int',
                  'description' => 'The nid of the node to update',
              ),
              array(
                  'name' => 'node',
                  'optional' => FALSE,
                  'source' => 'data',
                  'description' => 'The node data to update',
                  'type' => 'array',
              ),
          ),
          'access callback' => '_node_resource_access',
          'access arguments' => array( 'update' ),
          'access arguments append' => TRUE,
      ),
      'delete' => array(
          'help' => t('Delete a node'),
          'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/grow_records_resource' ),
          'callback' => '_delete',
          'args' => array(
              array(
                  'name' => 'nid',
                  'optional' => FALSE,
                  'source' => array( 'path' => 0 ),
                  'type' => 'int',
                  'description' => 'The nid of the node to delete',
              ),
          ),
          'access callback' => '_node_resource_access',
          'access arguments' => array( 'delete' ),
          'access arguments append' => TRUE,
      ),
      'index' => array(
          'help' => 'List all nodes',
          'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/grow_records_resource' ),
          'callback' => '_index',
          'args' => array(
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
                  'description' => 'Number of records to get per page.',
                  'default value' => variable_get('services_node_index_page_size', 10),
                  'source' => array( 'param' => 'pagesize' ),
              ),
          ),
          'access arguments' => array( 'access content' ),
      ),
  );
  return $definition;
}

/*
 * create 
 */

function _create($node) {
  if (isset($node['fid']) && $node['fid']) {
    $extra = _grow_records_extract($node['fid']);
  } elseif (isset($node['file']) && $node['file']) {
    $extra = _grow_records_extract($node['file']['file'], FALSE);
  }

  global $user;
  $obj = new stdClass();
  $obj->uid = $user->uid;
  $obj->type = 'grow_records';
  node_object_prepare($node);
  $obj->title = $node['title'];
  $obj->body['und'][0]['value'] = $node['body'];
  $obj->field_grow_records_file['und'][0]['fid'] = $node['fid'];
  $obj->field_grow_records_file['und'][0]['display'] = 1;
  $obj->field_grow_records_flags['und'][0]['value'] = $node['flags'];
  $obj->field_grow_records_circle['und'][0]['value'] = $node['circle'];
  $obj->field_grow_records_local_id['und'][0]['value'] = $node['local_id'];

  if (isset($extra['field_grow_records_img'])) {
    $obj->field_grow_records_img = $extra['field_grow_records_img'];
  }
  if (isset($extra['field_grow_records_voice'])) {
    $obj->field_grow_records_voice = $extra['field_grow_records_voice'];
    $obj->field_grow_records_voice['und'][0]['display'] = 1;
  }
  if (isset($extra['field_grow_records_video'])) {
    $obj->field_grow_records_video = $extra['field_grow_records_video'];
    $obj->field_grow_records_video['und'][0]['display'] = 1;
  }
  node_save($obj);
  $node = node_load($obj->nid);

  $nodes = _grow_records_format($node);
  return reset($nodes);
}

/*
 * update
 */

function _update($id, $data) {
  $node = _grow_records_format($data, 'node');
  $new = _node_resource_update($id, $node);
  $nodes = _grow_records_format(node_load($new['nid']));
  return reset($nodes);
}

/*
 * get single grow_records
 */

function _retrieve($nid) {
  $nodes = node_load_multiple(array( $nid ), array( 'type' => 'grow_records' ));
  $node = reset($nodes);
  if ($node) {
    $uri = entity_uri('node', $node);
    $node->path = url($uri['path'], array( 'absolute' => TRUE ));
    // Unset uri as it has complete entity and this
    // cause never ending recursion in rendering.
    unset($node->uri);
  }
  $data = _grow_records_format($node);
  return $data;
}

function _delete($nid) {
  return _node_resource_delete($nid);
}

/*
 * get grow_records list
 */

function _index($page, $fields, $parameters, $pagesize) {

  global $user;
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
      ->propertyCondition('status', 1)
      ->propertyCondition('type', 'grow_records');
  if ($parameters['uid']) {
    $query->propertyCondition('uid', $parameters['uid']);
  } else {
    $query->propertyCondition('uid', $user->uid);
  }
  if (isset($parameters['created'])) {
    if (is_array($parameters['created'])) {
      $query->propertyCondition('created', 0, '>');
      $query->propertyCondition('created', time(), '<');
    } else {
      $query->propertyCondition('created', $parameters['created'], '=');
    }
  }
  $fiter_query = $query;
  $result = $query->execute();

  $count = isset($result['node']) ? count($result['node']) : 0;
  if ($pagesize == -1) {
    $result = $fiter_query->execute();
    $data['count'] = $count;
  } else {
    $result = $fiter_query->range($page * $pagesize, $pagesize)->execute();
    $data['count'] = ceil($count / $pagesize);
  }


  if (isset($result['node'])) {
    $ids = array_keys($result['node']);
    $charts = _grow_records_format(node_load_multiple($ids), NULL, $fields);
  }
  $data['charts'] = $charts;
  $data['page'] = $page;
  $data['pagesize'] = $pagesize;
  return $data;
}

/*
 * request response data format
 */

function _grow_records_format($data, $target, $fields = '*') {
  if (isset($target) && $target == 'node') {
    foreach ($data as $k => $v) {
      switch ($k) {
        case 'title':
          $node['title'] = $v;
          break;
        case 'body':
          $node['body']['und'][0]['value'] = $v;
          break;
        case 'fid':
          $node['field_grow_records_file']['und'][0]['fid'] = $v;
          break;
        case 'flags':
          $node['field_grow_records_flags']['und'][0]['value'] = $v;
          break;
        case 'circle':
          $node['field_grow_records_circle']['und'][0]['value'] = $v;
          break;
        case 'local_id':
          $node['field_grow_records_local_id']['und'][0]['value'] = $v;
          break;
      }
    }
    $node['type'] = 'grow_records';
//        $node         = array(
//            'type' => 'grow_records',
//            'title' => $data['title'],
//            'body' => array(
//                'und' => array(
//                    array('value' => $data['body'])
//                ),
//            ),
//            'field_grow_records_file' => array(
//                'und' => array(
//                    array('fid' => $data['fid'])
//                ),
//            ),
//            'field_grow_records_flags' => array(
//                'und' => array(
//                    array(
//                        'value' => $data['flags']
//                    )
//                )
//            ),
//            'field_grow_records_circle' => array(
//                'und' => array(
//                    array(
//                        'value' => $data['circle']
//                    )
//                )
//            ),
//            'field_grow_records_local_id' => array(
//                'und' => array(
//                    array(
//                        'value' => $data['local_id']
//                    )
//                )
//            ),
//        );
    //$node['field_grow_records_local_id'][LANGUAGE_NONE][0]['value']['date'] = date('Y-m-d H:i:s', $data['local_id']);
    return $node;
  } else {
    if (!$data || empty($data)) {
      return array();
    }
    if (!is_array($data)) {
      $data = array( $data );
    }
    $format_data = array();
    foreach ($data as $node) {
      $chart = array(
          'chart_id' => $node->nid,
          'title' => $node->title,
          'body' => $node->body[LANGUAGE_NONE][0]['value'],
          'file' => file_create_url($node->field_grow_records_file[LANGUAGE_NONE][0]['uri']),
          'flags' => $node->field_grow_records_flags[LANGUAGE_NONE][0]['value'],
          'circle' => $node->field_grow_records_circle[LANGUAGE_NONE][0]['value'],
          'local_id' => $node->field_grow_records_local_id[LANGUAGE_NONE][0]['value'],
          'create_time' => $node->created,
          'modify_time' => $node->changed,
      );
      if ($fields != '*') {
        $field_chart = array();
        foreach (explode(',', $fields) as $field) {
          $field_chart[$field] = $chart[$field];
        }
        $format_data[] = $field_chart;
      } else {
        $format_data[] = $chart;
      }
    }
    return $format_data;
  }
}

function _grow_records_extract($data, $is_already_upload = TRUE) {
  module_load_include('inc', 'update', 'update.manager');
  if ($is_already_upload) {
    $file = file_load($data);
    $uri = $file->uri;
  } else {
    $uri = file_unmanaged_save_data(base64_decode($data), 'public://temp/' . time() . '.zip', FILE_EXISTS_REPLACE);
  }

  if (!isset($uri)) {
    return array();
  }

  $listContents = mutiple_extract_zip($uri);

  foreach ($listContents as $file) {
    $basename = basename($file);

    $file_name = explode('.', $basename);
    if (!isset($file_name[1])) {
      continue;
    }
    if (in_array($file_name[1], array( 'jpg', 'amr', '3gp' ))) {
      $file_data[$file_name[1]][] = array(
          'filesize' => filesize($file),
          'filename' => $basename,
          'file' => base64_encode(file_get_contents($file)),
          'filepath' => 'private://grow_records/' . uniqid() . '.'.$file_name[1],
      );
    }
  }
  foreach ($file_data as $type => $value) {
    foreach ($value as $v_file) {
      $after_files = _sbq_services_file_create($v_file);
      switch ($type) {
        case 'jpg':
          $node['field_grow_records_img']['und'][] = array( 'fid' => $after_files['fid'] );
          break;
        case 'amr':
          $node['field_grow_records_voice']['und'][] = array( 'fid' => $after_files['fid'], );
          break;
        case '3gp':
          $node['field_grow_records_video']['und'][] = array( 'fid' => $after_files['fid'], );
          break;
      }
    }
  }
  return isset($node) ? $node : array();
}

function mutiple_extract_zip($uri, $depth = 0, $temp = 'public://temp/') {
  if ($depth === 1) {
    $temp .= $depth . '/';
  }
  $archive = update_manager_archive_extract($uri, $temp);

  $file_list = array();
  foreach ($archive->listContents() as $file_name) {
    $full_file = drupal_realpath($temp) . '/' . $file_name;
    $arr_file = explode('.', $file_name);
    $uri = $temp . $file_name;
    if (is_array($arr_file) && $arr_file[1] == 'zip') {
      $depth_list = mutiple_extract_zip($uri, ++$depth, $temp); 
      $file_list = array_merge($file_list, $depth_list);
    } else {
      $file_list[] = $full_file;
    }
  }
  return $file_list;
}

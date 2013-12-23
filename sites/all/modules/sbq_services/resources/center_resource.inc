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
      'access arguments' => array( 'view' ),
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
  $definition['center']['relationships']['comment'] = array(
      'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/center_resource' ),
      'help' => 'This method returns center question comment.',
      'callback' => 'center_question_comment_query',
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
              'name' => 'questionid',
              'type' => 'int',
              'description' => t('The questionid .'),
              'source' => array( 'param' => 'questionid' ),
              'default value' => '',
              'optional' => FALSE,
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

  $definition['center']['relationships']['edu'] = array(
      'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/center_resource' ),
      'help' => 'This method returns center question.',
      'callback' => 'center_question_edu_query',
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

/**
 *  alter question function
 * @param type $centerid
 * @param type $fun
 * @param type $data
 * @return type
 */
function center_question_alter($centerid, $fun, $data) {

  if ($fun) {
    if (is_numeric($fun)) {
      $data['nid'] = $fun;
    } else {
      // return $fun;
      return call_user_func('center_question_' . $fun, $centerid, $data);
    }
  }

  $node = _center_question_format($centerid, $data);
  $node = reset($node);
  $node = _node_resource_create($node);
  return $node;
}

/**
 * create center question comment
 * @param type $centerid
 * @param type $data
 * @return type
 */
function center_question_comment($centerid, $data) {
  $result = _center_question_comment_formate($data);
  $node = reset($result);
  return _node_resource_create($node);
}

function center_question_comment_query($centerid, $fun = NULL, $questionid, $page, $fields, $parameters, $pagesize) {
  
  if ($fun) {
    if (is_numeric($fun)) {
      //$parameters['nid'] = $fun;
    } else {
      //return call_user_func('center_question_' . $fun, $page, $fields, $pagesize, $parameters, $centerid);
      return 'this interface is die';
    }
  }

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'answer')
      ->fieldCondition('field_answer', 'target_id', $questionid, '=');
  $node_query = clone $query;
  $count = $query->count()->execute();

  $result = $node_query->propertyOrderBy('created', 'DESC')
      ->range($page * $pagesize, $pagesize)
      ->execute();
  //return array_keys($result['node']);
  $nids = array();
  if (isset($result['node'])) {
    $nids = array_keys($result['node']);
  }

  $nodes = node_load_multiple($nids);  
  $nodes = _center_question_comment_formate($nodes, 'data', TRUE);

  $data = array(
      'data' => $nodes,
      'page' => $page,
      'pagecount' => ceil($count / $pagesize),
  );
  return $data;
}

/**
 * center question query
 * @param type $centerid
 * @param type $fun
 * @param type $page
 * @param type $fields
 * @param type $parameters
 * @param type $pagesize
 * @return type
 */
function center_question_query($centerid, $fun = NULL, $page, $fields, $parameters, $pagesize) {
  if ($fun) {
    if (is_numeric($fun)) {
      $parameters['nid'] = $fun;
    } else {
      return call_user_func('center_question_' . $fun, $page, $fields, $pagesize, $parameters, $centerid);
    }
  }
  $data = _center_question_query($fields, $parameters, $page, $pagesize, $centerid);
  if (isset($parameters['nid'])) {
    return $data;
    $nodes = _center_question_format($cneterid, $data['data'], 'data', TRUE);
    return reset($nodes);
  }

  $data['data'] = _center_question_format($cneterid, $data['data'], 'data', TRUE);
  return $data;
}

/**
 * selef center question query
 * @param type $fields
 * @param type $parameters
 * @param type $page
 * @param type $pagesize
 * @param type $centerid
 * @return type
 */
function _center_question_query($fields = "*", $parameters = array(), $page = 0, $pagesize = 10, $centerid) {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'question')
      ->fieldCondition('og_group_ref', 'target_id', $centerid, '=');

  foreach ($parameters as $key => $value) {
    $query->propertyCondition($key, $value);
  }
  $node_query = clone $query;
  $count = $query->count()->execute();

  $result = $node_query
      ->propertyOrderBy('created', 'DESC')
      ->range($page * $pagesize, $pagesize)
      ->execute();
  $nids = $result;
  if (isset($result['node'])) {
    $nids = array_keys($result['node']);
  }
  $nodes = node_load_multiple($nids);
  // include question comment
//  if ($nodes && isset($parameters['include_comment'])) {
//    if (!isset($parameters['include_comment']['page'])) {
//      $parameters['include_comment']['page'] = 0;
//    }
//    foreach ($nodes as $key => &$value) {
//      $commnet_count = count($value->field_answers['und']);
//      $commnet = array_values($value->field_answers['und']);
//      $result = array_slice($commnet, $parameters['include_comment']['page'] * 10, 10);
//      $value->comment_value = node_load($result);
//    }
//  }

  $data = array(
      'data' => $nodes,
      'page' => $page,
      'pagecount' => ceil($count / $pagesize),
  );
  return $data;
}

/**
 * center edu query
 * @param type $centerid
 * @param type $fun
 * @param type $page
 * @param type $fields
 * @param type $parameters
 * @param type $pagesize
 * @return type
 */
function center_question_edu_query($centerid, $fun = NULL, $page, $fields, $parameters, $pagesize) {
  if ($fun) {
    if (is_numeric($fun)) {
      $parameters['nid'] = $fun;
    } else {
      return call_user_func('center_question_' . $fun, $page, $fields, $pagesize, $parameters, $centerid);
    }
  }

  // 视频
  $view = views_get_view('sbq_center_edu');
  $view->set_display('center_edu_video');
  $view->set_arguments(array( $centerid ));
  $view->is_attachment = true;
  $view->execute();
  $view->preview();
  $video = array();
  foreach ($view->result as $key => $value) {
    $v['title'] = $value->node_title;
    $v['video'] = render($value->field_field_sbq_center_video[0]['rendered']);
    $v['video_url'] = file_create_url($value->field_field_sbq_center_video[0]['rendered']['#file']->uri);
    $video[] = $v;
  }
  // 文章
  $view_art = views_get_view('sbq_center_edu');
  $view_art->set_display('article_block');
  $view_art->set_arguments(array( $centerid ));
  $view_art->is_attachment = true;
  $view_art->execute();
  $view_art->preview();
  $article = array();
  foreach ($view_art->result as $key => $value) {
    $node = node_load($value->nid);
    $art['title'] = $value->node_title;
    $art['nid'] = $value->nid;
    $art['body'] = $node->body['und'][0]['value'];
    $article[] = $art;
  }
  return array( 'video' => $video, 'article' => $art );
}

/**
 * ceneter question covert data format between phone data, drupal node data
 * @param type $cneterid
 * @param type $data
 * @param type $target
 * @param type $is_list
 * @return type
 */
function _center_question_format($cneterid, $data, $target = 'node', $is_list = FALSE) {
  if (!$is_list) {
    $data = array( $data );
  }
  $result = array();
  foreach ($data as $key => $value) {
    $value = (array) $value;
    if ($target == 'node') {
      $node['title'] = $value['title'];
      $node['type'] = 'question';
      $node['body']['und'][0]['value'] = $value['body'];
      $node['og_group_ref']['und'][0]['target_id'] = $cneterid;
      $node['field_tags']['und'] = '中心问答';
      $node['type'] = 'question';
    } else {
      $node['body'] = $value['body']['und'][0]['value'];
      $node['title'] = $value['title'];
      $node['type'] = $value['type'];
      $node['created'] = $value['created'];
      $node['nid'] = $value['nid'];
      $node['comment'] = $value['comment'];
    }
    $result[] = $node;
  }

  return $result;
}

function _center_question_comment_formate($data, $target = 'node', $is_list = FALSE) {

  if (!$is_list) {
    $data = array( $data );
  }
  $result = array();
  foreach ($data as $key => $value) {
    $value = (array)$value;
    if ($target == 'node') {
      $node['title'] = $value['title'];
      $node['type'] = 'answer';
      $node['body']['und'][0]['value'] = $value['body'];
      $node['field_answer']['und'][0]['target_id'] = "1cc({$value['questionid']})";
    } else {
      $node['title'] = $value['title'];
      $node['type'] = $value['type'];
      $node['body'] = $value['body']['und'][0]['value'];
      $node['commentid'] = $value['nid'];
      $node['questionid'] = $value['field_answer']['und'][0]['target_id'];
    }
    $result[] = $node;
  }
  return $result;
}

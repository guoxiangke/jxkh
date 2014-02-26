<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function center_resource_definition() {
  module_load_include('inc', 'services', 'resources/node_resource');
  $definition['center']['operations'] = array(
      'retrieve' => array(
          'help' => 'Retrieve a center',
          'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/center_resource' ),
          'callback' => 'center',
          'args' => array(
              array(
                  'name' => 'centerid',
                  'optional' => FALSE,
                  'source' => array( 'path' => 0 ),
                  'type' => 'int',
                  'description' => 'The nid of the node to retrieve',
              ),
          ),
          'access callback' => '_node_resource_access',
          'access arguments' => array( 'view' ),
          'access arguments append' => TRUE,
      ),
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


  module_load_include('inc', 'webform_service', 'webform_service');
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
              'name' => 'data',
              'optional' => FALSE,
              'source' => 'data',
              'description' => 'The submission data to create',
              'type' => 'array',
          ),
      ),
//      'access callback' => '_submission_resource_access',
//      'access arguments' => array( 'create' ),
//      'access arguments append' => TRUE,
      'access callback' => '_node_resource_access',
      'access arguments' => array( 'view' ),
      'access arguments append' => TRUE,
  );

  $definition['center']['relationships']['reservation'] = array(
      'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/center_reservation_resource' ),
      'help' => 'This method returns center question.',
      'callback' => 'center_reservation_query',
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
              'type' => 'string',
              'description' => t('The function .'),
              'source' => array( 'path' => 2 ),
              'default value' => '',
              'optional' => TRUE,
          ),
          array(
              'name' => 'uid',
              'type' => 'int',
              'description' => t('The function .'),
              'source' => array( 'param' => 'uid' ),
              'default value' => 0,
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

  $definition['center']['targeted_actions']['message'] = array(
      'help' => 'send message to center user',
      'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/center_message_resource' ),
      'callback' => 'center_message_alter',
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
              'description' => 'alter center message function',
          ),
          array(
              'name' => 'data',
              'optional' => FALSE,
              'source' => 'data',
              'description' => 'The center message',
              'type' => 'array',
          ),
      ),
  );


  $definition['center']['relationships']['message'] = array(
      'file' => array( 'type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/center_message_resource' ),
      'help' => 'This method returns center message.',
      'callback' => 'center_message_query',
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

function center($centerid) {
  global $user;
  if (!$center = sbq_center_load($centerid)) {
    return services_error('not found the center form ' . $centerid, '404');
  }

  $nodes = _center_formate($center, 'data');

  module_load_include('inc', 'sbq_services', 'resources/center_message_resource');

  $message_new_count = db_select('pm_index', 'pmi')
      ->fields('pmi', array( 'mid' ))
      ->condition('is_new', 1)
      ->condition('recipient', $user->uid)
      ->condition('thread_id', center_message_get_privatemsgid($center->uid))
      ->condition('deleted', 0)
      ->execute()
      ->rowCount();
  //指导建议
  // 视频
  $view = views_get_view('sbq_center_edu');
  $view->set_display('center_edu_video');
  $view->set_arguments(array( $centerid ));
  $view->is_attachment = true;
  $view->execute();
  $view->preview();

  // 文章
  $view_art = views_get_view('sbq_center_edu');
  $view_art->set_display('article_block');
  $view_art->set_arguments(array( $centerid ));
  $view_art->is_attachment = true;
  $view_art->execute();
  $view_art->preview();
  $edu_count = count($view->result) + count($view_art->result);
  //预约门诊

  module_load_include('inc', 'sbq_services', 'resources/center_reservation_resource');
  $messages = center_reservation_message($centerid, $user->uid);

  $return = reset($nodes);

  $return['message'] = $message_new_count;
  $return['edu'] = $edu_count;
  $return['reservation'] = $messages;
  return $return;
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
  module_load_include('inc', 'media_youku', 'includes/MediaYouKuStreamWrapper');
  foreach ($view->result as $key => $value) {
    $media = new MediaYouKuStreamWrapper();
    $media->setUri($value->field_field_sbq_center_video[0]['rendered']['#file']->uri);
    $v['title'] = $value->node_title;
    $v['video'] = ''; //render($value->field_field_sbq_center_video[0]['rendered']);
    $v['thumb'] = file_create_url($media->getLocalThumbnailPath());
    $v['video_url'] = _center_formate_fetch_youku_video($media);
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
    $art['nid'] = (int) $value->nid;
    $art['body'] = $node->body['und'][0]['value'];
    $art['thumb'] = file_create_url($node->field_image['und'][0]['uri']);
    $article[] = $art;
  }
  return array( 'video' => $video, 'article' => $article );
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
      $node['nid'] = (int) $value['nid'];
      $node['comment'] = $value['comment'];
    }
    $result[] = $node;
  }

  return $result;
}

/**
 * convert data 
 * @param type $data
 * @param type $target
 * @param type $is_list
 * @return type
 */
function _center_question_comment_formate($data, $target = 'node', $is_list = FALSE) {

  if (!$is_list) {
    $data = array( $data );
  }
  $result = array();
  foreach ($data as $key => $value) {
    $value = (array) $value;
    if ($target == 'node') {
      $node['title'] = $value['title'];
      $node['type'] = 'answer';
      $node['body']['und'][0]['value'] = $value['body'];
      $node['field_answer']['und'][0]['target_id'] = "1cc({$value['questionid']})";
    } else {
      $node['title'] = $value['title'];
      $node['type'] = $value['type'];
      $node['body'] = $value['body']['und'][0]['value'];
      $node['commentid'] = (int) $value['nid'];
      $node['questionid'] = (int) $value['field_answer']['und'][0]['target_id'];
    }
    $result[] = $node;
  }
  return $result;
}

/**
 * convert center data
 * @param type $data
 * @param type $target
 * @param type $is_list
 * @return type
 */
function _center_formate($data, $target = 'node', $is_list = FALSE) {
  if (!$is_list) {
    $data = array( $data );
  }
  $nodes = array();
  foreach ($data as $key => $value) {
    $value = (array) $value;
    if ($target != 'node') {
      if (isset($value['field_sbq_center_img']['und'])) {
        //return $value['field_sbq_center_img']['und'];
        foreach ($value['field_sbq_center_img']['und'] as $key => $value) {
          $value = (array) $value;
          $node['open_img'][$key] = array(
              'url' => file_create_url($value['uri']),
              'name' => $value['filename'],
              'filesize' => $value['filesize'],
              'width' => $value['width'],
              'height' => $value['height'],
              'fid' => $value['fid'],
          );
        }
      }
    }
    if (isset($node)) {
      $nodes[] = $node;
    }
  }

  return $nodes;
}

/**
 *  get youku realpath
 * @param MediaYouKuStreamWrapper $media
 * @return type
 */
function _center_formate_fetch_youku_video(MediaYouKuStreamWrapper $media) {
//  if ($url = variable_get($media->getUri())) {
//    return $url;
//  }
  module_load_include('inc', 'sbq_services', 'resources/includes/youku_analysis');
  $parts = $media->get_parameters();
  $link = 'http://v.youku.com/player/getPlayList/VideoIDS/' . urlencode($parts['v']) . '/timezone/+08/version/5/source/out?password=&ran=2513&n=3';
  $content = file_get_contents($link);
  $data = @json_decode($content, true);

  foreach ($data['data'][0]['streamfileids'] AS $k => $v) {
    if ($k == 'mp4') {
      $sid = time() . (rand(0, 9000) + 10000);
      $fileid = getfileid($v, $data['data'][0]['seed']);
      $url = "http://f.youku.com/player/getFlvPath/sid/{$sid}_00/st/{$k}/fileid/{$fileid}?K={$data['data'][0]['segs'][$k][0]['k']}";
      variable_set($media->getUri(), $url);
      return $url;
    }
    continue;
  }

  return file_create_url($media->getUri());
}

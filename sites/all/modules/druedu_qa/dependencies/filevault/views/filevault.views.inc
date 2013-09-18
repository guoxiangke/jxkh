<?php

/**
 * @file
 * Providing extra functionality for the Model UI via views.
 */



/**
 * Implements hook_views_data()
 */
function filevault_views_data_alter(&$data) {

  $data['filevault']['id'] = array(
    'field' => array(
      'title' => t('Filevault ID'),
      'help' => t('The unique internal identifier of a filevault item.'),
      'handler' => 'filevault_handler_id',
    ),
  );
}

/**
 * Implements hook_views_default_views().
 */
function filevault_views_default_views() {
  $views = array();

  $view = new view;
  $view->name = 'Filevault Files';
  $view->description = 'A list of all files in the filevault';
  $view->tag = 'filevault';
  $view->base_table = 'filevault_files';
  $view->base_field = 'id';
  $view->human_name = 'Filevault';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['row_plugin'] = 'node';


  /* Field: Filevault: id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'filevault_files';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['id']['empty_zero'] = 0;

  /* Sort criterion: Content: Post date */
  //$handler->display->display_options['sorts']['created']['id'] = 'created';
  //$handler->display->display_options['sorts']['created']['table'] = 'filevault_files';
  //$handler->display->display_options['sorts']['created']['field'] = 'created';
  //$handler->display->display_options['sorts']['created']['order'] = 'DESC';

  /* Filter criterion: Content: Published */
  //$handler->display->display_options['filters']['status']['id'] = 'status';
  //$handler->display->display_options['filters']['status']['table'] = 'node';
  //$handler->display->display_options['filters']['status']['field'] = 'status';
  //$handler->display->display_options['filters']['status']['value'] = '1';
  //$handler->display->display_options['filters']['status']['group'] = 0;
  //$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'filevault/files';

  $views[$view->name] = $view;

  return $views;

}

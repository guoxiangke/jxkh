<?php

function _sbq_user_resource_definition() {
  module_load_include('inc', 'services', 'resources/user_resource');
  $definition = array(
      'sbq_user' => array(
          'operations' => array(
              'retrieve' => array(
                  'help' => 'Retrieve a user',
                  'callback' => '_user_resource_retrieve',
                  'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/user_resource'),
                  'access callback' => '_user_resource_access',
                  'access arguments' => array('view'),
                  'access arguments append' => TRUE,
                  'args' => array(
                      array(
                          'name' => 'uid',
                          'type' => 'int',
                          'description' => 'The uid of the user to retrieve.',
                          'source' => array('path' => 0),
                          'optional' => FALSE,
                      ),
                  ),
              ),
              'create' => array(
                  'help' => 'Create a user',
                  'callback' => '_user_resource_create',
                  'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/user_resource'),
                  'access callback' => '_user_resource_access',
                  'access arguments' => array('create'),
                  'access arguments append' => FALSE,
                  'args' => array(
                      array(
                          'name' => 'account',
                          'type' => 'array',
                          'description' => 'The user object',
                          'source' => 'data',
                          'optional' => FALSE,
                      ),
                  ),
              ),
              'update' => array(
                  'help' => 'Update a user',
                  'callback' => '_user_resource_update',
                  'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/user_resource'),
                  'access callback' => '_user_resource_access',
                  'access arguments' => array('update'),
                  'access arguments append' => TRUE,
                  'args' => array(
                      array(
                          'name' => 'uid',
                          'type' => 'int',
                          'description' => 'Unique identifier for this user',
                          'source' => array('path' => 0),
                          'optional' => FALSE,
                      ),
                      array(
                          'name' => 'data',
                          'type' => 'array',
                          'description' => 'The user object with updated information',
                          'source' => 'data',
                          'optional' => FALSE,
                      ),
                  ),
              ),
              'delete' => array(
                  'help' => 'Delete a user',
                  'callback' => '_user_resource_delete',
                  'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/user_resource'),
                  'access callback' => '_user_resource_access',
                  'access arguments' => array('delete'),
                  'access arguments append' => TRUE,
                  'args' => array(
                      array(
                          'name' => 'uid',
                          'type' => 'int',
                          'description' => 'The id of the user to delete',
                          'source' => array('path' => 0),
                          'optional' => FALSE,
                      ),
                  ),
              ),
              'index' => array(
                  'help' => 'List all users',
                  'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/user_resource'),
                  'callback' => '_user_resource_index',
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
                          'description' => 'Parameters',
                          'default value' => array(),
                          'source' => array('param' => 'parameters'),
                      ),
                      array(
                          'name' => 'pagesize',
                          'optional' => TRUE,
                          'type' => 'int',
                          'description' => 'Number of records to get per page.',
                          'default value' => variable_get('services_user_index_page_size', 20),
                          'source' => array('param' => 'pagesize'),
                      ),
                  ),
                  'access arguments' => array('access user profiles'),
                  'access arguments append' => FALSE,
              ),
          ),
          'actions' => array(
              'sbq_login' => array(
                  'help' => 'Login a user for a new session',
                  'callback' => '_sbq_user_resource_login',
                  'args' => array(
                      array(
                          'name' => 'username',
                          'type' => 'string',
                          'description' => 'A valid username',
                          'source' => array('data' => 'username'),
                          'optional' => FALSE,
                      ),
                      array(
                          'name' => 'password',
                          'type' => 'string',
                          'description' => 'A valid password',
                          'source' => array('data' => 'password'),
                          'optional' => FALSE,
                      ),
                  ),
                  'access callback' => 'services_access_menu',
                  'file' => array('type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/sbq_user_resource'),
              ),
              'sbq_logout' => array(
                  'file' => array('type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/sbq_user_resource'),
                  'help' => 'Logout a user session',
                  'callback' => 'sbq_user_resource_logout',
                  'access callback' => 'services_access_menu',
              ),
              'token' => array(
                  'file' => array(
                      'type' => 'inc',
                      'module' => 'services',
                      'name' => 'user_resource',
                  ),
                  'callback' => '_user_resource_get_token',
                  'access callback' => 'services_access_menu',
                  'help' => t('Returns the CSRF token.'),
              ),
          ),
      ),
  );

  $definition['user']['actions']['register'] = array_merge($definition['sbq_user']['operations']['create'], array(
      'help' => 'Register a user',
          ));

  return $definition;
}

function _sbq_user_resource_login($username, $password) {
  $data = _user_resource_login($username, $password);
  return $data;
}

function sbq_user_resource_logout(){
  return _user_resource_logout();
}

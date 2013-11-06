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
        'delete' => array(
            'help' => t('Delete a node'),
            'file' => array('type' => 'inc', 'module' => 'sbq_services', 'name' => 'resources/grow_records_resource'),
            'callback' => '_delete',
            'args' => array(
                array(
                    'name' => 'nid',
                    'optional' => FALSE,
                    'source' => array('path' => 0),
                    'type' => 'int',
                    'description' => 'The nid of the node to delete',
                ),
            ),
            'access callback' => '_node_resource_access',
            'access arguments' => array('delete'),
            'access arguments append' => TRUE,
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
                    'default value' => variable_get('services_node_index_page_size', 10),
                    'source' => array('param' => 'pagesize'),
                ),
            ),
            'access arguments' => array('access content'),
        ),
    );
    return $definition;
}

/*
 * create 
 */

function _create($node) {
    $node  = _grow_records_format($node, 'node');
    $node  = _node_resource_create($node);
    $nodes = _grow_records_format(node_load($node['nid']));
    return reset($nodes);
}

/*
 * get single grow_records
 */

function _retrieve($nid) {
    $nodes = node_load_multiple(array($nid), array('type' => 'grow_records'));
    $node  = reset($nodes);
    if ($node) {
        $uri        = entity_uri('node', $node);
        $node->path = url($uri['path'], array('absolute' => TRUE));
        // Unset uri as it has complete entity and this
        // cause never ending recursion in rendering.
        unset($node->uri);
    }
    $data = _grow_records_format($node);
    return reset($data);
}

function _delete($nid) {
    return _node_resource_delete($nid);
}

/*
 * get grow_records list
 */

function _index($page, $fields, $parameters, $page_size = 10) {
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
    if ($parameters['created']) {
        if (is_array($parameters['created'])) {
            $query->propertyCondition('created', 0, '>');
            $query->propertyCondition('created', time(), '<');
        } else {
            $query->propertyCondition('created', $parameters['created'], '=');
        }
    }
    $fiter_query = $query;
    $result      = $query->execute();

    $count  = isset($result['node']) ? count($result['node']) : 0;
    $result = $fiter_query->range($page * $page_size, $page_size)->execute();

    if (isset($result['node'])) {
        $ids            = array_keys($result['node']);
        $data['charts'] = _grow_records_format(node_load_multiple($ids));
    }
    $data['count']    = ceil($count / $page_size);
    $data['index']    = $page;
    $data['pagesize'] = $page_size;
    return $data;
}

/*
 * request response data format
 */

function _grow_records_format($data, $target) {
    if (isset($target) && $target == 'node') {
        $node = array(
            'type' => 'grow_records',
            'title' => $data['title'],
            'body' => array(
                'und' => array(
                    array('value' => $data['body'])
                ),
            ),
            'field_grow_records_file' => array(
                'und' => array(
                    array('fid' => $data['fid'])
                ),
            ),
            'field_grow_records_flags' => array(
                'und' => array(
                    array(
                        'value' => $data['flags']
                    )
                )
            ),
            'field_grow_records_circle' => array(
                'und' => array(
                    array(
                        'value' => $data['circle']
                    )
                )
            ),
            'field_grow_records_local_id' => array(
                'und' => array(
                    array(
                        'value' => $data['local_id']
                    )
                )
            ),
        );
        //$node['field_grow_records_local_id'][LANGUAGE_NONE][0]['value']['date'] = date('Y-m-d H:i:s', $data['local_id']);
        return $node;
    } else {
        if (!$data || empty($data)) {
            return array();
        }
        if (!is_array($data)) {
            $data = array($data);
        }
        $format_data = array();
        foreach ($data as $node) {
            $format_data[] = array(
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
        }
        return $format_data;
    }
}

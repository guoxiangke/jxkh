<?php
/**
 * @file
 * sbq_event_features.features.inc
 */

/**
 * Implements hook_node_info().
 */
function sbq_event_features_node_info() {
  $items = array(
    'event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('活动名称'),
      'help' => '',
    ),
  );
  return $items;
}

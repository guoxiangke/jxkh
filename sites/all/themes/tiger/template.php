<?php

/**
 * @file template.php
 */

/**
 * hook_preprocess_page
 *
 */
function tiger_preprocess_page($variables) {
  // /* can be used to load css per page, based on path, node-type, or others. */
  if ($variables['is_front']) {
    drupal_add_css(drupal_get_path('theme', 'tiger') . "/css/home_style.css");
  }
}

/**
 * hook_preprocess_node
 *
 */
function tiger_preprocess_node($variables) {
  // /* can be used to load css per page, based on path, node-type, or others. */
  // if (drupal_get_path_alias("node/{$variables['#node']->nid}") == 'foo') {
  //   drupal_add_css(drupal_get_path('theme', 'tiger') . "/css/foo.css");
  // }
}

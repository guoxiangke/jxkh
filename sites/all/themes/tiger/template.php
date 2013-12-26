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
  // front page
  if ($variables['is_front']) {
    drupal_add_css(path_to_theme() . "/css/home_style.css", array('group' => CSS_THEME));
  }
  // login page and register page
  if (!$variables['logged_in']) {
    drupal_add_css(path_to_theme() . "/css/reg.css", array('group' => CSS_THEME));
  }
  // question detail page
  if (arg(0) == 'question') {
    drupal_add_css(path_to_theme() . "/css/question.css", array('group' => CSS_THEME));
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

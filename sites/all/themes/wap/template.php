<?php


/**
 * hook_preprocess_page
 *
 */
function wap_preprocess_page(&$variables) {
  // /* can be used to load css per page, based on path, node-type, or others. */
  // weixin
  if (in_array('weixin', arg())) {
    $variables['theme_hook_suggestions'][] = 'page__weixin';
    $variables['page']['sidebar_first'] = FALSE;
    $variables['page']['sidebar_second'] = FALSE;
    if (!isset($variables['node'])) {
      $tid = arg(3);
    }
    $weixin_id = wap_get_weixin_id($tid);
    $variables['weixin_id'] = $weixin_id;
    $variables['weixin_index'] = '/wap/weixin/articles/'.$weixin_id;
    $active_tid = wap_get_active_tid($tid, $weixin_id);
    $weixin_menu = wap_get_weixin_menu($weixin_id, $active_tid);
    $variables['weixin_menu'] = $weixin_menu;
  }
  if (isset($variables['node']) && $variables['node']->type == 'weixin') {
    $variables['theme_hook_suggestions'][] = 'page__weixin';
    $variables['page']['sidebar_first'] = FALSE;
    $variables['page']['sidebar_second'] = FALSE;
    $node = $variables['node'];
    if ($node->field_wx_service['und'][0]['tid']) {
      $tid = $node->field_wx_service['und'][0]['tid'];
    }
    $weixin_id = wap_get_weixin_id($tid);
    $variables['weixin_id'] = $weixin_id;
    $variables['weixin_index'] = '/wap/weixin/articles/'.$weixin_id;
    $active_tid = wap_get_active_tid($tid, $weixin_id);
    $weixin_menu = wap_get_weixin_menu($weixin_id, $active_tid);
    $variables['weixin_menu'] = $weixin_menu;
  }
}

function wap_get_weixin_menu($weixin_id, $active_tid=0) {
  $vocabulary = taxonomy_vocabulary_machine_name_load('wx_service');
  $vid = $vocabulary->vid;
  $p_terms = taxonomy_get_tree($vid, $weixin_id, 1);
  $p_terms_count = count($p_terms);
  $weixin_menu = '';
  if ($p_terms_count > 0) {
    $weixin_menu.='<ul>';
    foreach ($p_terms as $p_key => $p_term) {
      $p_name = trim($p_term->name);
      $p_tid = trim($p_term->tid);
      $p_active = '';
      if ($p_tid == $active_tid) {
        $p_active = ' class="active"';
      }
      $c_terms = taxonomy_get_tree($vid, $p_tid, 1);
      $c_terms_count = count($c_terms);
      if ($c_terms_count > 0 && strlen(trim($p_name))>0) {
        $weixin_menu .= '<li'.$p_active.'>'.l($p_name, 'wap/weixin/articles/'.$p_tid).'</li>';
      }
    }
    $weixin_menu.='</ul>';
  }
  return $weixin_menu;
}

function wap_get_weixin_id($tid) {
  if (is_numeric($tid)) {
    $term_tid = $tid;
    //this will be your top parent term if any was found
    $term = taxonomy_term_load($tid);
    $top_parent_term = null;
    $parent_terms = taxonomy_get_parents_all($term_tid);
    //top parent term has no parents so find it out by checking if it has parents
    foreach($parent_terms as $parent) {
      $parent_parents = taxonomy_get_parents_all($parent->tid);
      if ($parent_parents != false) {
        //this is top parent term
        $top_parent_term = $parent;
      }
    }
    $weixin_id = $top_parent_term->tid;
  }
  return $weixin_id;
}

function wap_get_active_tid($tid, $weixin_id) {
  if (is_numeric($tid)) {
    $term_tid = $tid;
    //this will be your top parent term if any was found
    $term = taxonomy_term_load($tid);
    $parent_terms = taxonomy_get_parents($term_tid);
    //top parent term has no parents so find it out by checking if it has parents
    foreach($parent_terms as $parent) {
      $p_tid = $parent->tid;
      if ($p_tid == $weixin_id) {
        $active_tid = $term_tid;
      } else {
        $active_tid = $p_tid;
      }
    }
  }
  return $active_tid;
}

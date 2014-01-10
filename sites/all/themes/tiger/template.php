<?php

/**
 * @file template.php
 */

/**
 * hook_preprocess_page
 *
 */
function tiger_preprocess_page(&$variables) {
  // /* can be used to load css per page, based on path, node-type, or others. */
  // front page
  if ($variables['is_front']) {
    drupal_add_css(path_to_theme() . "/css/home_style.css", array('group' => CSS_THEME));
  }
  // login page and register page
  if (!$variables['logged_in'] && arg(0) == 'user') {
    drupal_add_css(path_to_theme() . "/css/reg.css", array('group' => CSS_THEME));
  }
  // question page
  if (arg(0) == 'question' || arg(0) == 'questions') {
    drupal_add_css(path_to_theme() . "/css/question.css", array('group' => CSS_THEME));
    if (is_numeric(arg(1)) && ! arg(2)) {
      $node = node_load(arg(1));
      drupal_set_title($node->title);
    }
  }
  // user center page
  if (arg(0) == 'user') {
    drupal_add_css(path_to_theme() . "/css/user.css", array('group' => CSS_THEME));

    global $user;
    $variables['user'] = $user;
    if (is_numeric(arg(1)) && arg(1)!=$user->uid) {
      $account = user_load(arg(1));
    } else {
      $account = $user;
    }
    $variables['account'] = $account;
    $variables['counts'] = array(
      'user_post_count' => sbq_commons_get_count($account->uid, 'post'),
      'user_message_count' => sbq_commons_messages_count($account),
      'user_blog_count' => sbq_commons_get_count($account->uid, 'blog'),
      'user_question_count' => sbq_commons_get_count($account->uid, 'question'),
      'user_answer_count' => sbq_commons_get_count($account->uid, 'answer'),
      'user_relationship_count' => sbq_user_relationships_my_relstionships($account),
      'user_point_count' => userpoints_get_current_points($user->uid, 'all'),
    );
    $variables['follow_link'] = sbq_user_relationships_action_between_user($user, $account);
    $variables['menu_sbq_user_center'] = menu_navigation_links('menu-sbq-user-center');
    $variables['is_doctor'] = FALSE;
    if (in_array('doctor', $account->roles)) {
      $a_doctor_profile = profile2_load_by_user($account, 'doctor_profile');
      $variables['is_doctor'] = TRUE;
      $variables['a_doctor_profile'] = $a_doctor_profile;
      $variables['field_doctor_title'] = drupal_render(field_view_field('profile2', $a_doctor_profile, 'field_doctor_title', 'value'));
      $variables['field_doctor_hospitals'] = drupal_render(field_view_field('profile2', $a_doctor_profile, 'field_doctor_hospitals', 'value'));
      $variables['field_doctor_departments'] = drupal_render(field_view_field('profile2', $a_doctor_profile, 'field_doctor_departments', 'value'));
      $variables['hospitals_departments'] = $field_doctor_hospitals .' '. $field_doctor_departments;
    }
  }
  // blog detial page
  if (isset($variables['node']) && $variables['node']->type == 'blog') {
    $node = $variables['node'];
    drupal_add_css(path_to_theme() . "/css/user.css", array('group' => CSS_THEME));
    $variables['theme_hook_suggestions'][] = 'page__user';
    $account = user_load($node->uid);
    $variables['account'] = $account;
    $variables['counts'] = array(
      'user_post_count' => sbq_commons_get_count($account->uid, 'post'),
      'user_message_count' => sbq_commons_messages_count($account),
      'user_blog_count' => sbq_commons_get_count($account->uid, 'blog'),
      'user_question_count' => sbq_commons_get_count($account->uid, 'question'),
      'user_answer_count' => sbq_commons_get_count($account->uid, 'answer'),
      'user_relationship_count' => sbq_user_relationships_my_relstionships($account),
      'user_point_count' => userpoints_get_current_points($user->uid, 'all'),
    );
    $variables['follow_link'] = sbq_user_relationships_action_between_user($user, $account);
  }

}

function tiger_preprocess_views_view(&$vars) {
  if ($vars['view']->name == 'questions' && $vars['view']->current_display == 'page_questions_tagged') {
    $title = $vars['view']->exposed_input['field_tags_tid'];
    if (strlen(trim($title))>0) {
      $vars['title'] = $title;
      $vars['view']->build_info['title'] = $title;
    } else {
      $vars['title'] = '问答';
      $vars['view']->build_info['title'] = '问答';
    }
  }
  if ($vars['view']->name == 'sbq_user_center') {
    global $user;
    if (is_numeric(arg(1)) && arg(1)!=$user->uid) {
      $account = user_load(arg(1));
    } else {
      $account = $user;
    }
    $vars['account'] = $account;

    $blog_active = FALSE;
    if (in_array('blog', arg())) {
      $blog_active = TRUE;
      $menu_promoted_active = '';
      $menu_blog_active = '';
      if (in_array('promoted', arg())) {
        $menu_promoted_active = 'class="active"';
      } else {
        $menu_blog_active = 'class="active"';
      }
    }
    $vars['blog_active'] = $blog_active;
    $vars['menu_promoted_active'] = $menu_promoted_active;
    $vars['menu_blog_active'] = $menu_blog_active;

    $qa_active = FALSE;
    if (in_array('qa', arg())) {
      $qa_active = TRUE;
      $menu_promoted_active = '';
      $menu_followed_active = '';
      $menu_ask_active = '';
      $menu_answer_active = '';
      if (in_array('promoted', arg())) {
        $menu_promoted_active = 'class="active"';
      } elseif (in_array('followed', arg())) {
        $menu_followed_active = 'class="active"';
      } elseif (in_array('ask', arg())) {
        $menu_ask_active = 'class="active"';
      } elseif (in_array('answer', arg())) {
        $menu_answer_active = 'class="active"';
      }
    }
    $vars['qa_active'] = $qa_active;
    $vars['menu_promoted_active'] = $menu_promoted_active;
    $vars['menu_followed_active'] = $menu_followed_active;
    $vars['menu_ask_active'] = $menu_ask_active;
    $vars['menu_answer_active'] = $menu_answer_active;
  }
}

/**
 * hook_preprocess_node
 *
 */
function tiger_preprocess_node(&$variables) {
  // /* can be used to load css per page, based on path, node-type, or others. */
  // if (drupal_get_path_alias("node/{$variables['#node']->nid}") == 'foo') {
  //   drupal_add_css(drupal_get_path('theme', 'tiger') . "/css/foo.css");
  // }
  $news_array = array('news', 'hospital_blacklist', 'friend_activities', 'red_list', 'black_list', 'doctor_legend');
  if (in_array($variables['type'], $news_array)) {
    //$node = $variables['node'];
    drupal_add_css(path_to_theme() . "/css/news.css", array('group' => CSS_THEME));
    $variables['theme_hook_suggestions'][] = 'node__news';
  }
}

function tiger_pager($variables) {
  global $pager_page_array, $pager_total;

  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('« first')), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('next ›')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last »')), 'element' => $element, 'parameters' => $parameters));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array('pager-first'),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('pager-previous'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('active'),
            'data' => $i,
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('pager-next'),
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
        'class' => array('pager-last'),
        'data' => $li_last,
      );
    }
    $output = theme('item_list', array(
      'items' => $items,
      'attributes' => array('class' => array('pager')),
    ));
    return '<div class="sbq_page_num">'.$output.'</div>';
  }
}

function tiger_theme() {
  $items = array();
  $items['user_login'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'tiger') . '/templates',
    'template' => 'user-login',
    'preprocess functions' => array(
       'tiger_preprocess_user_login'
    ),
  );
  // $items['user_register_form'] = array(
  //   'render element' => 'form',
  //   'path' => drupal_get_path('theme', 'tiger') . '/templates',
  //   'template' => 'user-register-form',
  //   'preprocess functions' => array(
  //     'tiger_preprocess_user_register_form'
  //   ),
  // );
  return $items;
}

function tiger_preprocess_user_login(&$vars) {
  // $vars['form']['actions']['submit']['#attributes']['class'][] = 'sbq_login_btn';
  // $vars['form']['actions']['#field_prefix'] = '<div class="sbq_botton_01">';
  // $vars['form']['actions']['#field_suffix'] = '</div>';
}

function tiger_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'user_login') {
    # code...
    //unset($form['name']['#title']);
    unset($form['name']['#description']);
    $form['name']['#title'] = '用户名';
    $form['name']['#prefix'] = '<div class="sbq_form_01">';
    $form['name']['#attributes']['class'][] = 'sbq_input_01';
    $form['name']['#suffix'] = '<div class="sbq_link"><a href="/user/register" class="reg cboxElement" target="_parent">注册账户</a></div></div>';

    //unset($form['pass']['#title']);
    unset($form['pass']['#description']);
    $form['pass']['#prefix'] = '<div class="sbq_form_01">';
    $form['pass']['#attributes']['class'][] = 'sbq_input_01';
    $form['pass']['#suffix'] = '<div class="sbq_link"><a href="#">忘记密码？</a></div></div>';

    //unset($form['remember_me']['#title']);
    $form['remember_me']['#prefix'] = '<div class="sbq_checkbox_01">';
    $form['remember_me']['#suffix'] = '</div>';

    $form['actions']['submit']['#value'] = '登录';
    $form['actions']['submit']['#attributes']['class'][] = 'sbq_login_btn';
    $form['actions']['submit']['#ajax'] = array(
      'callback' => 'tiger_user_login_ajax_callback',
      'wrapper' => '',
      'method' => 'replace',
    );
    $form['actions']['#prefix'] = '<div class="sbq_botton_01"><label></label>';
    $form['actions']['#suffix'] = '</div>';
  }
}

function tiger_user_login_ajax_callback() {
  return '<script type="text/javascript">
    parent.$.fn.colorbox.close();
    location.reload(true);
  </script>';
}

/**
 * Implements theme_menu_tree().
 */
function tiger_menu_tree($variables) {
  return '<ul>' . $variables['tree'] . '</ul>';
}

/**
 * Implements hook_html_head_alter().
 */
function tiger_html_head_alter(&$head_elements) {
  unset($head_elements['system_meta_generator']);
}

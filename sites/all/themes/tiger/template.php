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
  if (!$variables['logged_in'] && arg(0) == 'user' && (arg(1) == 'login' || in_array('register', arg()))) {
    drupal_add_css(path_to_theme() . "/css/reg.css", array('group' => CSS_THEME));
    drupal_add_css(path_to_theme() . "/css/form.css", array('group' => CSS_THEME));
    $variables['page']['sidebar_second'] = FALSE;
    $variables['theme_hook_suggestions'][] = 'page__user';
  }
  // login page
  if (!$variables['logged_in'] && arg(0) == 'user' && arg(1) == 'login') {
    drupal_add_js(path_to_theme() . "/js/login.js");
  }
  // register page
  if (!$variables['logged_in'] && arg(1) == 'register') {
    drupal_add_css(path_to_theme() . "/css/reg.css", array('group' => CSS_THEME));
    drupal_add_css(path_to_theme() . "/css/form.css", array('group' => CSS_THEME));
    $variables['page']['sidebar_second'] = FALSE;
  }
  // news list page
  if (in_array('news', arg())) {
    drupal_add_css(path_to_theme() . "/css/news.css", array('group' => CSS_THEME));
  }
  // question page
  if (arg(0) == 'question' || arg(0) == 'questions') {
    drupal_add_css(path_to_theme() . "/css/question.css", array('group' => CSS_THEME));
    if (arg(0) == 'question') {
      $qa_nid = arg(1);
      $center_nid = _sbq_center_get_nid_by_node($qa_nid);
      if ($center_nid) {
        drupal_add_css(path_to_theme() . "/css/hospital.css", array('group' => CSS_THEME));
        $variables['theme_hook_suggestions'][] = 'page__center';
        $variables['page']['sidebar_second'] = FALSE;
        $variables['center_id'] = $center_nid;
        $expert_nid = _sbq_center_expert_nid_get($center_nid);
        $variables['expert_nid'] = $expert_nid;
      }
    }
  }
  // user center page
  //if ($variables['logged_in'] && arg(0) == 'user') {
  if (arg(0) == 'user') {
    // drupal_add_css(path_to_theme() . "/css/user.css", array('group' => CSS_THEME));
    if (!$variables['logged_in'] && count(arg()) == 1) {
      drupal_add_css(path_to_theme() . "/css/reg.css", array('group' => CSS_THEME));
      drupal_add_css(path_to_theme() . "/css/form.css", array('group' => CSS_THEME));
      $variables['page']['sidebar_second'] = FALSE;
    } else {
      drupal_add_css(path_to_theme() . "/css/user.css", array('group' => CSS_THEME));
    }

    global $user;
    $variables['user'] = $user;
    if (is_numeric(arg(1)) && arg(1)!=$user->uid) {
      $account = user_load(arg(1));
    } else {
      $account = $user;
    }
    $variables['account'] = $account;
    if ($variables['logged_in'] || is_numeric(arg(1))) {
      $name = $account->name;
      $title = $name.'的个人主页';
      drupal_set_title($title);
    }

    if (module_exists('sbq_commons')) {
      $user_post_count = sbq_commons_get_count($account->uid, 'post');
      $user_message_count = sbq_commons_messages_count($account);
      $user_blog_count = sbq_commons_get_count($account->uid, 'blog');
      $user_question_count = sbq_commons_get_count($account->uid, 'question');
      $user_answer_count = sbq_commons_get_count($account->uid, 'answer');
    } else {
      $user_post_count = 0;
      $user_message_count = 0;
      $user_blog_count = 0;
      $user_question_count = 0;
      $user_answer_count = 0;
    }
    if (module_exists('sbq_user_relationships')) {
      $user_relationship_count = sbq_user_relationships_my_relstionships($account);
      $follow_link = sbq_user_relationships_action_between_user($user, $account);
    } else {
      $user_relationship_count = 0;
      $follow_link = '';
    }
    if ($variables['logged_in'] && module_exists('userpoints')) {
      $user_point_count = userpoints_get_current_points($user->uid, 'all');
    } else {
      $user_point_count = 0;
    }
    $variables['counts'] = array(
      'user_post_count' => $user_post_count,
      'user_message_count' => $user_message_count,
      'user_blog_count' => $user_blog_count,
      'user_question_count' => $user_question_count,
      'user_answer_count' => $user_answer_count,
      'user_relationship_count' => $user_relationship_count,
      'user_point_count' => $user_point_count,
    );
    $variables['follow_link'] = $follow_link;
    $variables['menu_sbq_user_center'] = menu_navigation_links('menu-sbq-user-center');
    $variables['is_doctor'] = FALSE;
    if (in_array('doctor', $account->roles) && module_exists('profile2')) {
      $a_doctor_profile = profile2_load_by_user($account, 'doctor_profile');
      $variables['is_doctor'] = TRUE;
      $variables['a_doctor_profile'] = $a_doctor_profile;
      $field_author = field_view_field('profile2', $a_doctor_profile, 'field_author', 'value');
      $variables['field_author'] = drupal_render($field_author);
      $field_doctor_title = field_view_field('profile2', $a_doctor_profile, 'field_doctor_title', 'value');
      $variables['field_doctor_title'] = drupal_render($field_doctor_title);
      $field_hospital_name = field_view_field('profile2', $a_doctor_profile, 'field_hospital_name', 'value');
      $variables['field_hospital_name'] = drupal_render($field_hospital_name);
      $field_department = field_view_field('profile2', $a_doctor_profile, 'field_department', 'value');
      $variables['field_department'] = drupal_render($field_department);
      $variables['hospitals_departments'] = $variables['field_hospital_name'] .' '. $variables['field_department'];
    }
  }
  // user edit page
  if ($variables['logged_in'] && arg(0) == 'user' && in_array('edit', arg())) {
    drupal_add_css(path_to_theme() . "/css/form.css", array('group' => CSS_THEME));
  }
  // blog detial page
  if (isset($variables['node']) && $variables['node']->type == 'blog') {
    global $user;
    $node = $variables['node'];
    drupal_add_css(path_to_theme() . "/css/user.css", array('group' => CSS_THEME));
    $variables['theme_hook_suggestions'][] = 'page__user';
    $account = user_load($node->uid);
    $variables['account'] = $account;
    if (module_exists('sbq_commons')) {
      $user_post_count = sbq_commons_get_count($account->uid, 'post');
      $user_message_count = sbq_commons_messages_count($account);
      $user_blog_count = sbq_commons_get_count($account->uid, 'blog');
      $user_question_count = sbq_commons_get_count($account->uid, 'question');
      $user_answer_count = sbq_commons_get_count($account->uid, 'answer');
    } else {
      $user_post_count = 0;
      $user_message_count = 0;
      $user_blog_count = 0;
      $user_question_count = 0;
      $user_answer_count = 0;
    }
    if (module_exists('sbq_user_relationships')) {
      $user_relationship_count = sbq_user_relationships_my_relstionships($account);
      $follow_link = sbq_user_relationships_action_between_user($user, $account);
    } else {
      $user_relationship_count = 0;
      $follow_link = '';
    }
    if (module_exists('userpoints')) {
      $user_point_count = userpoints_get_current_points($user->uid, 'all');
    } else {
      $user_point_count = 0;
    }

    $variables['counts'] = array(
      'user_post_count' => $user_post_count,
      'user_message_count' => $user_message_count,
      'user_blog_count' => $user_blog_count,
      'user_question_count' => $user_question_count,
      'user_answer_count' => $user_answer_count,
      'user_relationship_count' => $user_relationship_count,
      'user_point_count' => $user_point_count,
    );
    $variables['follow_link'] = $follow_link;
    $variables['is_doctor'] = FALSE;
    if (in_array('doctor', $account->roles) && module_exists('profile2')) {
      $a_doctor_profile = profile2_load_by_user($account, 'doctor_profile');
      $variables['is_doctor'] = TRUE;
      $variables['a_doctor_profile'] = $a_doctor_profile;
      $field_author = field_view_field('profile2', $a_doctor_profile, 'field_author', 'value');
      $variables['field_author'] = drupal_render($field_author);
      $field_doctor_title = field_view_field('profile2', $a_doctor_profile, 'field_doctor_title', 'value');
      $variables['field_doctor_title'] = drupal_render($field_doctor_title);
      $field_hospital_name = field_view_field('profile2', $a_doctor_profile, 'field_hospital_name', 'value');
      $variables['field_hospital_name'] = drupal_render($field_hospital_name);
      $field_department = field_view_field('profile2', $a_doctor_profile, 'field_department', 'value');
      $variables['field_department'] = drupal_render($field_department);
      $variables['hospitals_departments'] = $variables['field_hospital_name'] .' '. $variables['field_department'];
    }
  }
  // blog/question add page
  if ((in_array('blog', arg()) || in_array('question', arg())) && in_array('add', arg())) {
    global $user;
    drupal_add_css(path_to_theme() . "/css/user.css", array('group' => CSS_THEME));
    drupal_add_css(path_to_theme() . "/css/form.css", array('group' => CSS_THEME));
    $variables['theme_hook_suggestions'][] = 'page__user';
    $account = $user;
    $variables['account'] = $account;
    if (module_exists('sbq_commons')) {
      $user_post_count = sbq_commons_get_count($account->uid, 'post');
      $user_message_count = sbq_commons_messages_count($account);
      $user_blog_count = sbq_commons_get_count($account->uid, 'blog');
      $user_question_count = sbq_commons_get_count($account->uid, 'question');
      $user_answer_count = sbq_commons_get_count($account->uid, 'answer');
    } else {
      $user_post_count = 0;
      $user_message_count = 0;
      $user_blog_count = 0;
      $user_question_count = 0;
      $user_answer_count = 0;
    }
    if (module_exists('sbq_user_relationships')) {
      $user_relationship_count = sbq_user_relationships_my_relstionships($account);
      $follow_link = sbq_user_relationships_action_between_user($user, $account);
    } else {
      $user_relationship_count = 0;
      $follow_link = '';
    }
    if (module_exists('userpoints')) {
      $user_point_count = userpoints_get_current_points($user->uid, 'all');
    } else {
      $user_point_count = 0;
    }

    $variables['counts'] = array(
      'user_post_count' => $user_post_count,
      'user_message_count' => $user_message_count,
      'user_blog_count' => $user_blog_count,
      'user_question_count' => $user_question_count,
      'user_answer_count' => $user_answer_count,
      'user_relationship_count' => $user_relationship_count,
      'user_point_count' => $user_point_count,
    );
    $variables['follow_link'] = $follow_link;
  }
  // center page
  if (arg(0) == 'center') {
    drupal_add_css(path_to_theme() . "/css/hospital.css", array('group' => CSS_THEME));
    $center_nid = arg(1);
    //var_dump($center_nid);die();
    $variables['center_id'] = $center_nid;
    $expert_nid = _sbq_center_expert_nid_get($center_nid);
    $variables['expert_nid'] = $expert_nid;
    $variables['page']['sidebar_second'] = FALSE;
    if (in_array('reservation', arg()) && in_array('created', arg())) {
      drupal_add_css(path_to_theme() . "/css/form.css", array('group' => CSS_THEME));
    }
    if (!$variables['logged_in'] && in_array('reservation', arg()) && in_array('my', arg())) {
      // TODO: hook_menu_alert or something else to control access
      $variables['page']['content']['system_main']['main']['#markup'] = 'Access denied';
    }
    if (in_array('info', arg())) {
      drupal_add_css(path_to_theme() . "/css/news.css", array('group' => CSS_THEME));
    }
  }
  if (isset($variables['node']) && $variables['node']->type == 'sbq_center_edu') {
    drupal_add_css(path_to_theme() . "/css/hospital.css", array('group' => CSS_THEME));
    drupal_add_css(path_to_theme() . "/css/news.css", array('group' => CSS_THEME));
    $variables['theme_hook_suggestions'][] = 'page__center';
    $variables['page']['sidebar_second'] = FALSE;
    $node = $variables['node'];
    $center_nid = $node->og_group_ref['und']['0']['target_id'];
    $variables['center_id'] = $center_nid;
    $expert_nid = _sbq_center_expert_nid_get($center_nid);
    $variables['expert_nid'] = $expert_nid;
  }
  if (isset($variables['node']) && $variables['node']->type == 'center_notice') {
    drupal_add_css(path_to_theme() . "/css/hospital.css", array('group' => CSS_THEME));
    drupal_add_css(path_to_theme() . "/css/news.css", array('group' => CSS_THEME));
    $variables['theme_hook_suggestions'][] = 'page__center';
    $variables['page']['sidebar_second'] = FALSE;
    $node = $variables['node'];
    $center_nid = $node->og_group_ref['und']['0']['target_id'];
    $variables['center_id'] = $center_nid;
    $expert_nid = _sbq_center_expert_nid_get($center_nid);
    $variables['expert_nid'] = $expert_nid;
  }
  if (arg(0) == 'messages') {
    global $user;
    $center_nid = _sbq_center_nid_get();
    if ($center_nid) {
      drupal_add_css(path_to_theme() . "/css/hospital.css", array('group' => CSS_THEME));
      $variables['theme_hook_suggestions'][] = 'page__center';
      $variables['center_id'] = $center_nid;
      $expert_nid = _sbq_center_expert_nid_get($center_nid);
      $variables['expert_nid'] = $expert_nid;
      $variables['page']['sidebar_second'] = FALSE;
    }
    if (arg(1) == 'view') {
      $variables['page']['content']['system_main']['#prefix'] = '<div class="sbq_pm">';
      $variables['page']['content']['system_main']['#suffix'] = '</div>';

      $variables['page']['content']['system_main']['messages']['#prefix'] = '<div class="sbq_pm_wrap">';
      $variables['page']['content']['system_main']['messages']['#suffix'] = '</div>';

      $variables['page']['content']['system_main']['participants']['#prefix'] = '<div class="sbq_hide">';
      $variables['page']['content']['system_main']['participants']['#suffix'] = '</div>';
    }
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

    $follower_active = FALSE;
    $sbq_quick_ask_form = '';

    $menu_qa_active = '';
    $menu_blog_active = '';
    if (in_array('followers', arg())) {
      $follower_active = TRUE;
      if (in_array('qa', arg())) {
        $menu_qa_active = 'class="active"';
      } else {
        $menu_blog_active = 'class="active"';
      }
      if ($user->uid) {
        module_load_include('inc', 'node', 'node.pages');
        $node = (object) array(
          'uid' => $user->uid,
          'name' => (isset($user->name) ? $user->name : ''),
          'type' => 'question',
          'language' => LANGUAGE_NONE
        );
        $question_node_form = drupal_get_form('question_node_form', $node);
        $sbq_quick_ask_form = render($question_node_form);
      }
    }
    $vars['follower_active'] = $follower_active;
    $vars['quick_ask_form'] = $sbq_quick_ask_form;
    $vars['menu_qa_active'] = $menu_qa_active;
    $vars['menu_blog_active'] = $menu_blog_active;

    $blog_active = FALSE;

    $menu_promoted_active = '';
    $menu_blog_active = '';
    if (in_array('blog', arg())) {
      $blog_active = TRUE;
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
    $menu_promoted_active = '';
    $menu_followed_active = '';
    $menu_ask_active = '';
    $menu_answer_active = '';
    if (in_array('qa', arg())) {
      $qa_active = TRUE;
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
  if ($vars['view']->name == 'question' && $vars['view']->current_display == 'single_question_page') {
    $vars['is_center'] = FALSE;
    $center_nid = $vars['view']->field['og_group_ref']->original_value;
    if ($center_nid) {
      $vars['is_center'] = TRUE;
    }
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
  $news_array = array(
    'news',
    'hospital_blacklist',
    'friend_activities',
    'red_list',
    'black_list',
    'doctor_legend'
  );
  if (in_array($variables['type'], $news_array)) {
    drupal_add_css(path_to_theme() . "/css/news.css", array('group' => CSS_THEME));
    $variables['theme_hook_suggestions'][] = 'node__news';
  }
  if ($variables['type'] == 'page') {
    drupal_add_css(path_to_theme() . "/css/news.css", array('group' => CSS_THEME));
    $variables['theme_hook_suggestions'][] = 'node__page';
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

    $form['#prefix'] = '<div class="sbq_login"><div class="sbq_reg_nav">'
        .'<ul>'
          .'<li class="active"><a class="sbq_reg_l"></a></li>'
        .'</ul>'
      .'</div>'
      .'<div class="sbq_reg_content"><div class="sbq_form_wrap">';
    $form['#suffix'] = '</div></div></div>';

    unset($form['name']['#description']);
    $form['name']['#title'] = '用户名';
    $form['name']['#prefix'] = '<div class="sbq_form_01">';
    $form['name']['#attributes']['class'][] = 'sbq_input_01';
    $form['name']['#suffix'] = '<div class="sbq_link"><a href="/customer/register">注册账户</a></div></div>';

    unset($form['pass']['#description']);
    $form['pass']['#prefix'] = '<div class="sbq_form_01">';
    $form['pass']['#attributes']['class'][] = 'sbq_input_01';
    $form['pass']['#suffix'] = '<div class="sbq_link"><a href="/user/password">忘记密码？</a></div></div>';

    $form['remember_me']['#prefix'] = '<div class="sbq_checkbox_01">';
    $form['remember_me']['#suffix'] = '</div>';

    $form['actions']['submit']['#value'] = '登录';
    $form['actions']['submit']['#attributes']['class'][] = 'sbq_login_btn';
    // $form['actions']['submit']['#ajax'] = array(
    //   'callback' => 'tiger_user_login_ajax_callback',
    //   'wrapper' => $form['#id'],
    //   'method' => 'replace',
    //   'progress' => array( 'type' => 'throbber', 'message' => '请稍候' ),
    // );
    $form['actions']['#prefix'] = '<div class="sbq_botton_01"><label></label>';
    $form['actions']['#suffix'] = '</div>';
  } elseif ($form_id == 'user_register_form') {
    global $user;

    $js_settings = array(
      'password' => array(
        'strengthTitle' => t('Password strength:'),
        'hasWeaknesses' => t('To make your password stronger:'),
        'tooShort' => '',
        'addLowerCase' => '',
        'addUpperCase' => '',
        'addNumbers' => '',
        'addPunctuation' => '',
        'sameAsUsername' => t('Make it different from your username'),
        'confirmSuccess' => t('yes'),
        'confirmFailure' => t('no'),
        'weak' => t('Weak'),
        'fair' => t('Fair'),
        'good' => t('Good'),
        'strong' => t('Strong'),
        'confirmTitle' => t('Passwords match:'),
        'username' => (isset($user->name) ? $user->name : ''),
      ),
    );
    static $already_added = FALSE;
    if (!$already_added) {
      $already_added = TRUE;
      $element['#attached']['js'][] = array('data' => $js_settings, 'type' => 'setting');
    }

    $user_reg_active = '';
    $doctor_reg_active = '';
    $reg = arg(0);
    $is_doctor_reg = FALSE;
    if ($reg) {
      if ($reg == 'customer') {
        $user_reg_active = 'class="active"';
      } elseif ($reg == 'doctor') {
        $doctor_reg_active = 'class="active"';
        $is_doctor_reg = TRUE;
      }
    }
    $form['#prefix'] = '<div class="sbq_reg"><div class="sbq_reg_nav">'
        .'<ul>'
          .'<li '.$user_reg_active.'><a href="/customer/register" class="sbq_reg_u"></a></li>'
          .'<li '.$doctor_reg_active.'><a href="/doctor/register" class="sbq_reg_d"></a></li>'
        .'</ul>'
      .'</div>'
      .'<div class="sbq_reg_content"><div class="sbq_form_wrap">';
    $form['#suffix'] = '</div></div></div>';

    //unset($form['account']['name']['#description']);
    $form['account']['name']['#prefix'] = '<div class="sbq_form_01">';
    $form['account']['name']['#attributes']['class'][] = 'sbq_input_01';
    $form['account']['name']['#suffix'] = '</div>';

    $form['account']['name']['#attributes']['autocomplete'] = 'off';
    $form['account']['mail']['#attributes']['autocomplete'] = 'off';
    $form['account']['pass']['#attributes']['autocomplete'] = 'off';
    //unset($form['account']['mail']['#description']);
    $form['account']['mail']['#prefix'] = '<div class="sbq_form_01">';
    $form['account']['mail']['#attributes']['class'][] = 'sbq_input_01';
    $form['account']['mail']['#suffix'] = '</div>';

    //unset($form['account']['pass']['#description']);
    $form['account']['pass']['#attributes']['class'][] = 'sbq_input_01';

    $form['agree']['#prefix'] = '<div class="sbq_checkbox_01">';
    $form['agree']['#suffix'] = '</div>';

    $form['actions']['submit']['#value'] = '注册';
    $form['actions']['submit']['#attributes']['class'][] = 'sbq_login_btn';
    $form['actions']['#prefix'] = '<div class="sbq_botton_01"><label></label>';
    $form['actions']['#suffix'] = '</div>';

    if ($is_doctor_reg) {
      // profile_doctor_profile
      $form['profile_doctor_profile']['field_author']['#prefix'] = '<div class="sbq_form_01">';
      $form['profile_doctor_profile']['field_author']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
      $form['profile_doctor_profile']['field_author']['#suffix'] = '</div>';

      $form['profile_doctor_profile']['field_hospital_name']['#prefix'] = '<div class="sbq_form_01">';
      $form['profile_doctor_profile']['field_hospital_name']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
      $form['profile_doctor_profile']['field_hospital_name']['#suffix'] = '</div>';

      $form['profile_doctor_profile']['field_department']['#prefix'] = '<div class="sbq_form_01">';
      $form['profile_doctor_profile']['field_department']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
      $form['profile_doctor_profile']['field_department']['#suffix'] = '</div>';

      $form['profile_doctor_profile']['field_doctor_title']['#prefix'] = '<div class="sbq_form_01">';
      $form['profile_doctor_profile']['field_doctor_title']['#suffix'] = '</div>';

      $form['profile_doctor_profile']['field_patient_diseases']['#prefix'] = '<div class="sbq_form_01">';
      $form['profile_doctor_profile']['field_patient_diseases']['#suffix'] = '</div>';

      $form['profile_doctor_profile']['field_introduction']['#prefix'] = '<div class="sbq_form_01">';
      $form['profile_doctor_profile']['field_introduction']['#suffix'] = '</div>';

      // profile_doctor_private_profile
      if (isset($form['profile_doctor_private_profile']['field_phone_number'])) {
        $form['profile_doctor_private_profile']['field_phone_number']['#prefix'] = '<div class="sbq_form_01">';
        $form['profile_doctor_private_profile']['field_phone_number']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
        $form['profile_doctor_private_profile']['field_phone_number']['#suffix'] = '</div>';
      }
      if (isset($form['profile_doctor_private_profile']['field_doctor_hospital_phone'])) {
        $form['profile_doctor_private_profile']['field_doctor_hospital_phone']['#prefix'] = '<div class="sbq_form_01">';
        $form['profile_doctor_private_profile']['field_doctor_hospital_phone']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
        $form['profile_doctor_private_profile']['field_doctor_hospital_phone']['#suffix'] = '</div>';
      }
      if (isset($form['profile_doctor_private_profile']['field_image'])) {
        $form['profile_doctor_private_profile']['field_image']['#prefix'] = '<div class="sbq_form_01">';
        $form['profile_doctor_private_profile']['field_image']['#suffix'] = '</div>';
      }
      if (isset($form['profile_doctor_private_profile']['field_license'])) {
        $form['profile_doctor_private_profile']['field_license']['#prefix'] = '<div class="sbq_form_01">';
        $form['profile_doctor_private_profile']['field_license']['#suffix'] = '</div>';
      }
      if (isset($form['profile_doctor_private_profile']['field_license_num'])) {
        $form['profile_doctor_private_profile']['field_license_num']['#prefix'] = '<div class="sbq_form_01">';
        $form['profile_doctor_private_profile']['field_license_num']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
        $form['profile_doctor_private_profile']['field_license_num']['#suffix'] = '</div>';
      }
    } else {
      if (isset($form['profile_customer_profile']['field_patient_diseases'])) {
        $form['profile_customer_profile']['field_patient_diseases']['#prefix'] = '<div class="sbq_hide sbq_form_01">';
        $form['profile_customer_profile']['field_patient_diseases']['#suffix'] = '</div>';
      }
      if (isset($form['profile_customer_profile']['field_job'])) {
        $form['profile_customer_profile']['field_job']['#prefix'] = '<div class="sbq_hide sbq_form_01">';
        $form['profile_customer_profile']['field_job']['#suffix'] = '</div>';
      }
      if (isset($form['profile_customer_profile']['field_sex'])) {
        $form['profile_customer_profile']['field_sex']['#prefix'] = '<div class="sbq_hide sbq_form_01">';
        $form['profile_customer_profile']['field_sex']['und']['#attributes']['class'][] = 'sbq_radio_wrap';
        $form['profile_customer_profile']['field_sex']['#suffix'] = '</div>';
      }
      if (isset($form['profile_customer_profile']['field_patient_diseases'])) {
        $form['profile_customer_profile']['field_nickname']['#prefix'] = '<div class="sbq_hide sbq_form_01">';
        $form['profile_customer_profile']['field_nickname']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
        $form['profile_customer_profile']['field_nickname']['#suffix'] = '</div>';
      }
      if (isset($form['profile_customer_profile']['field_patient_diseases'])) {
        unset($form['profile_customer_profile']['field_birthday']['und']['#prefix']);
        unset($form['profile_customer_profile']['field_birthday']['und']['#suffix']);
        $form['profile_customer_profile']['field_birthday']['#prefix'] = '<div class="sbq_hide sbq_form_01">';
        $form['profile_customer_profile']['field_birthday']['#suffix'] = '</div>';
      }
    }
  } elseif ($form_id == 'blog_node_form') {
    $form['#prefix'] = '<div class="sbq_add_content"><div class="sbq_head"><div class="sbq_title">发布文章</div></div>';
    $form['#suffix'] = '</div>';

    $form['title']['#prefix'] = '<div class="sbq_form_02">';
    $form['title']['#suffix'] = '</div>';

    $form['body']['#prefix'] = '<div class="sbq_form_02">';
    $form['body']['#suffix'] = '</div>';

    $form['field_tags']['#prefix'] = '<div class="sbq_form_02">';
    $form['field_tags']['#suffix'] = '</div>';
  } elseif ($form_id == 'question_node_form') {
    $is_followers_page = FALSE;
    if (in_array('followers', arg())) {
      $is_followers_page = TRUE;
    }

    if ($is_followers_page) {
      $form['#prefix'] = '<div class="sbq_add_content sbq_form_wrap">';
      $form['#suffix'] = '</div>';

      $form['body']['und'][0]['#format'] = 'plain_text';

      $form['field_tags']['#prefix'] = '<div class="sbq_hide">';
      $form['field_tags']['#suffix'] = '</div>';
    } else {
      $form['#prefix'] = '<div class="sbq_add_content"><div class="sbq_head"><div class="sbq_title">发布问题</div></div>';
      $form['#suffix'] = '</div>';

      $form['field_tags']['#prefix'] = '<div class="sbq_form_02">';
      $form['field_tags']['#suffix'] = '</div>';

      $form['body']['#prefix'] = '<div class="sbq_form_02">';
      $form['body']['#suffix'] = '</div>';
    }

    $form['title']['#prefix'] = '<div class="sbq_form_02">';
    $form['title']['#suffix'] = '</div>';

    $form['field_departments']['#prefix'] = '<div class="sbq_hide">';
    $form['field_departments']['#suffix'] = '</div>';

    $form['og_group_ref']['#prefix'] = '<div class="sbq_hide">';
    $form['og_group_ref']['#suffix'] = '</div>';
  } elseif ($form_id == 'user_profile_form') {
    if (arg(0) == 'user' && arg(1) == 'reset' && in_array('brief', arg())) {
      $form['#prefix'] = '<div class="sbq_findpwd"><div class="sbq_findpwd_nav">'
        .'</div>'
        .'<div class="sbq_reg_content">'
        .'<div class="sbq_step">
            <ul>
              <li class="done"><span>1<em>发送认证邮件</em></span></li>
              <li class="cur"><span>2<em>重置密码</em></span></li>
              <li class="last"><span>3<em>完成</em></span></li>
            </ul>
          </div>'
        .'<div class="sbq_form_wrap">';
      $form['#suffix'] = '</div></div></div>';

      $form['actions']['submit']['#value'] = '下一步';
      $form['actions']['submit']['#attributes']['class'][] = 'sbq_login_btn';
      $form['actions']['#prefix'] = '<div class="sbq_botton_01"><label></label>';
      $form['actions']['#suffix'] = '</div>';
    } else {
      $is_doctor = FALSE;
      $roles_array = $form['#user']->roles;
      if  (in_array('doctor', $roles_array)) {
        $is_doctor = TRUE;
      }
      $menu_edit_active = '';
      $menu_doctor_active = '';
      $menu_doctor_private_active = '';
      $menu_customer_active = '';
      $menu_patient_private_active = '';
      if (in_array('doctor_profile', arg())) {
        $menu_doctor_active = ' class="active"';
      } elseif (in_array('doctor_private_profile', arg())) {
        $menu_doctor_private_active = ' class="active"';
      } elseif (in_array('customer_profile', arg())) {
        $menu_customer_active = ' class="active"';
      } elseif (in_array('patient_private_profile', arg())) {
        $menu_patient_private_active = ' class="active"';
      } else {
        $menu_edit_active = ' class="active"';
      }
      $prefix = '<div class="sbq_nav">'
        .'<ul>'
          .'<li>'.l('资料', 'user/'.$form['#user']->uid).'</li>'
          .'<li'.$menu_edit_active.'>'.l('编辑账户资料', 'user/'.$form['#user']->uid.'/edit').'</li>';
      if ($is_doctor) {
        $prefix .= '<li'.$menu_doctor_active.'>'.l('编辑医生注册信息', 'user/'.$form['#user']->uid.'/edit/doctor_profile').'</li>'
          .'<li'.$menu_doctor_private_active.'>'.l('编辑医生认证信息', 'user/'.$form['#user']->uid.'/edit/doctor_private_profile').'</li>';
      } else {
        $prefix .= '<li'.$menu_customer_active.'>'.l('编辑患者公开信息', 'user/'.$form['#user']->uid.'/edit/customer_profile').'</li>'
          .'<li'.$menu_patient_private_active.'>'.l('编辑患者私人信息', 'user/'.$form['#user']->uid.'/edit/patient_private_profile').'</li>';
      }
      $prefix .= '</ul>'
        .'</div>'
        .'<div class="sbq_user_date"><div class="sbq_form_wrap">';
      $form['#prefix'] = $prefix;
      $form['#suffix'] = '</div></div>';

      //unset($form['account']['current_pass']['#description']);
      $form['account']['current_pass']['#prefix'] = '<div class="sbq_form_01">';
      $form['account']['current_pass']['#attributes']['class'][] = 'sbq_input_01';
      $form['account']['current_pass']['#suffix'] = '</div>';

      //unset($form['account']['mail']['#description']);
      $form['account']['mail']['#prefix'] = '<div class="sbq_form_01">';
      $form['account']['mail']['#attributes']['class'][] = 'sbq_input_01';
      $form['account']['mail']['#attributes']['disabled'] = 'disabled';
      $form['account']['mail']['#suffix'] = '</div>';

      //unset($form['account']['pass']['#description']);
      $form['account']['pass']['#attributes']['class'][] = 'sbq_input_01';

      unset($form['picture']['picture_delete']);
      $form['picture']['#prefix'] = '<div class="sbq_form_01">';
      $form['picture']['#suffix'] = '</div>';

      if ($is_doctor) {
        if (isset($form['profile_doctor_profile']['field_hospital_name'])) {
          $form['profile_doctor_profile']['field_hospital_name']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_doctor_profile']['field_hospital_name']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
          $form['profile_doctor_profile']['field_hospital_name']['#suffix'] = '</div>';
        }
        if (isset($form['profile_doctor_profile']['field_department'])) {
          $form['profile_doctor_profile']['field_department']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_doctor_profile']['field_department']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
          $form['profile_doctor_profile']['field_department']['#suffix'] = '</div>';
        }
        if (isset($form['profile_doctor_profile']['field_author'])) {
          $form['profile_doctor_profile']['field_author']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_doctor_profile']['field_author']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
          $form['profile_doctor_profile']['field_author']['#suffix'] = '</div>';
        }
        if (isset($form['profile_doctor_profile']['field_introduction'])) {
          $form['profile_doctor_profile']['field_introduction']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_doctor_profile']['field_introduction']['#suffix'] = '</div>';
        }
        if (isset($form['profile_doctor_profile']['field_doctor_title'])) {
          $form['profile_doctor_profile']['field_doctor_title']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_doctor_profile']['field_doctor_title']['#suffix'] = '</div>';
        }
        if (isset($form['profile_doctor_profile']['field_patient_diseases'])) {
          $form['profile_doctor_profile']['field_patient_diseases']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_doctor_profile']['field_patient_diseases']['#suffix'] = '</div>';
        }
        // profile_doctor_private_profile
        if (isset($form['profile_doctor_private_profile']['field_phone_number'])) {
          $form['profile_doctor_private_profile']['field_phone_number']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_doctor_private_profile']['field_phone_number']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
          $form['profile_doctor_private_profile']['field_phone_number']['#suffix'] = '</div>';
        }
        if (isset($form['profile_doctor_private_profile']['field_doctor_hospital_phone'])) {
          $form['profile_doctor_private_profile']['field_doctor_hospital_phone']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_doctor_private_profile']['field_doctor_hospital_phone']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
          $form['profile_doctor_private_profile']['field_doctor_hospital_phone']['#suffix'] = '</div>';
        }
        if (isset($form['profile_doctor_private_profile']['field_image'])) {
          $form['profile_doctor_private_profile']['field_image']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_doctor_private_profile']['field_image']['#suffix'] = '</div>';
        }
        if (isset($form['profile_doctor_private_profile']['field_license'])) {
          $form['profile_doctor_private_profile']['field_license']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_doctor_private_profile']['field_license']['#suffix'] = '</div>';
        }
        if (isset($form['profile_doctor_private_profile']['field_license_num'])) {
          $form['profile_doctor_private_profile']['field_license_num']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_doctor_private_profile']['field_license_num']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
          $form['profile_doctor_private_profile']['field_license_num']['#suffix'] = '</div>';
        }
      }
      if (isset($form['profile_customer_profile'])) {
        if (isset($form['profile_customer_profile']['field_patient_diseases'])) {
          $form['profile_customer_profile']['field_patient_diseases']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_customer_profile']['field_patient_diseases']['#suffix'] = '</div>';
        }
        if (isset($form['profile_doctor_profile']['field_job'])) {
          $form['profile_customer_profile']['field_job']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_customer_profile']['field_job']['#suffix'] = '</div>';
        }
        if (isset($form['profile_doctor_profile']['field_sex'])) {
          $form['profile_customer_profile']['field_sex']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_customer_profile']['field_sex']['und']['#attributes']['class'][] = 'sbq_radio_wrap';
          $form['profile_customer_profile']['field_sex']['#suffix'] = '</div>';
        }
        if (isset($form['profile_customer_profile']['field_nickname'])) {
          $form['profile_customer_profile']['field_nickname']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_customer_profile']['field_nickname']['und'][0]['value']['#attributes']['class'][] = 'sbq_input_01';
          $form['profile_customer_profile']['field_nickname']['#suffix'] = '</div>';
        }
        if (isset($form['profile_customer_profile']['field_birthday'])) {
          unset($form['profile_customer_profile']['field_birthday']['und']['#prefix']);
          unset($form['profile_customer_profile']['field_birthday']['und']['#suffix']);
          $form['profile_customer_profile']['field_birthday']['#prefix'] = '<div class="sbq_form_01">';
          $form['profile_customer_profile']['field_birthday']['#suffix'] = '</div>';
        }
      }

      $form['actions']['submit']['#attributes']['class'][] = 'sbq_btn';
      $form['actions']['#prefix'] = '<div class="sbq_botton_01"><label></label>';
      $form['actions']['#suffix'] = '</div>';
    }
  } elseif ($form_id == 'user_pass') {
    $form['#prefix'] = '<div class="sbq_findpwd"><div class="sbq_findpwd_nav">'

      .'</div>'
      .'<div class="sbq_reg_content">'
      .'<div class="sbq_step">
          <ul>
            <li class="cur"><span>1<em>发送认证邮件</em></span></li>
            <li><span>2<em>重置密码</em></span></li>
            <li class="last"><span>3<em>完成</em></span></li>
          </ul>
        </div>'
      .'<div class="sbq_form_wrap">';
    $form['#suffix'] = '</div></div></div>';

    $form['name']['#prefix'] = '<div class="sbq_form_01">';
    $form['name']['#attributes']['class'][] = 'sbq_input_01';
    $form['name']['#suffix'] = '</div>';

    $form['actions']['submit']['#value'] = '下一步';
    $form['actions']['submit']['#attributes']['class'][] = 'sbq_login_btn';
    $form['actions']['#prefix'] = '<div class="sbq_botton_01"><label></label>';
    $form['actions']['#suffix'] = '</div>';
  } elseif ($form_id == 'user_pass_reset') {
    $form['#prefix'] = '<div class="sbq_findpwd"><div class="sbq_findpwd_nav">'
      .'</div>'
      .'<div class="sbq_reg_content">'
      .'<div class="sbq_step">
          <ul>
            <li class="done"><span>1<em>发送认证邮件</em></span></li>
            <li class="cur"><span>2<em>重置密码</em></span></li>
            <li class="last"><span>3<em>完成</em></span></li>
          </ul>
        </div>'
      .'<div class="sbq_form_wrap"><div class="sbq_text">';
    $form['#suffix'] = '</div></div></div></div>';

    $form['actions']['submit']['#value'] = '下一步';
    $form['actions']['submit']['#attributes']['class'][] = 'sbq_login_btn';
    $form['actions']['#prefix'] = '<div class="sbq_botton_01"><label></label>';
    $form['actions']['#suffix'] = '</div>';
  } elseif ($form_id == 'webform_client_form_23343') {
    $form['#prefix'] = '<div class="sbq_form_wrap">';
    $form['#suffix'] = '</div>';

    $form['submitted']['name']['#prefix'] = '<div class="sbq_form_01">';
    $form['submitted']['name']['#attributes']['class'][] = 'sbq_input_01';
    $form['submitted']['name']['#suffix'] = '</div>';

    $form['submitted']['telphone']['#prefix'] = '<div class="sbq_form_01">';
    $form['submitted']['telphone']['#attributes']['class'][] = 'sbq_input_01';
    $form['submitted']['telphone']['#suffix'] = '</div>';

    $form['submitted']['email']['#prefix'] = '<div class="sbq_form_01">';
    $form['submitted']['email']['#attributes']['class'][] = 'sbq_input_01';
    $form['submitted']['email']['#suffix'] = '</div>';

    $form['submitted']['zhicheng']['#prefix'] = '<div class="sbq_form_01">';
    $form['submitted']['zhicheng']['#attributes']['class'][] = 'sbq_input_01';
    $form['submitted']['zhicheng']['#suffix'] = '</div>';

    $form['submitted']['yiyuan']['#prefix'] = '<div class="sbq_form_01">';
    $form['submitted']['yiyuan']['#attributes']['class'][] = 'sbq_input_01';
    $form['submitted']['yiyuan']['#suffix'] = '</div>';

    $form['submitted']['keshi']['#prefix'] = '<div class="sbq_form_01">';
    $form['submitted']['keshi']['#attributes']['class'][] = 'sbq_input_01';
    $form['submitted']['keshi']['#suffix'] = '</div>';

    $form['submitted']['app_more']['#prefix'] = '<div class="sbq_form_01">';
    $form['submitted']['app_more']['#attributes']['class'][] = 'sbq_input_01';
    $form['submitted']['app_more']['#suffix'] = '</div>';

    $form['actions']['submit']['#value'] = '提交';
    $form['actions']['submit']['#attributes']['class'][] = 'sbq_btn';
    $form['actions']['#prefix'] = '<div class="sbq_botton_01"><label></label>';
    $form['actions']['#suffix'] = '</div>';
  } elseif ($form_id == 'sbq_center_reservation_node_form') {
    $center_calendar = views_embed_view('calendar_for_reservation', $display_id = 'page_4');
    $center_notice = views_embed_view('center_notice', $display_id = 'block_1');
    $para = drupal_get_query_parameters();
    $date = $para['date'];
    $date = str_replace('10:00', '上午', $date);
    $date = str_replace('14:00', '下午', $date);
    $form['#prefix'] = '<div class="hospital_order_add">
      <div class="sbq_wrap">
        <div class="sbq_head">请登记患者信息</div>
        <div class="sbq_form_wrap">
          <div class="sbq_form_01">
            <label>预约时间</label>
            <div class="sbq_text">'.$date.'</div>
        </div>';
    $form['#suffix'] = '</div></div>';

    $form['field_visited']['#prefix'] = '<div class="sbq_form_01">';
    $form['field_visited']['#attributes']['class'][] = 'sbq_input_01';
    $form['field_visited']['#suffix'] = '</div>';

    $form['field_case_num']['#prefix'] = '<div id="sbq_case_num" class="sbq_form_01">';
    $form['field_case_num']['#attributes']['class'][] = 'sbq_input_01';
    $form['field_case_num']['#suffix'] = '</div>';

    $form['field_real_name']['#prefix'] = '<div class="sbq_form_01">';
    $form['field_real_name']['#attributes']['class'][] = 'sbq_input_01';
    $form['field_real_name']['#suffix'] = '</div>';

    $form['field_age']['#prefix'] = '<div class="sbq_form_01">';
    $form['field_age']['#attributes']['class'][] = 'sbq_input_01';
    $form['field_age']['#suffix'] = '</div>';

    $form['field_sex']['#prefix'] = '<div class="sbq_form_01">';
    $form['field_sex']['#attributes']['class'][] = 'sbq_input_01';
    $form['field_sex']['#suffix'] = '</div>';

    $form['field_identity']['#prefix'] = '<div class="sbq_form_01">';
    $form['field_identity']['#attributes']['class'][] = 'sbq_input_01';
    $form['field_identity']['#suffix'] = '</div>';

    $form['field_phone']['#prefix'] = '<div class="sbq_form_01">';
    $form['field_phone']['#attributes']['class'][] = 'sbq_input_01';
    $form['field_phone']['#suffix'] = '</div>';

    $form['body']['#prefix'] = '<div class="sbq_form_01">';
    $form['body']['#suffix'] = '</div>';

    $form['field_reservation_status']['#prefix'] = '<div class="sbq_hide">';
    $form['field_reservation_status']['#suffix'] = '</div>';

    $form['field_reservation_time']['#prefix'] = '<div class="sbq_hide">';
    $form['field_reservation_time']['#suffix'] = '</div>';

    $form['og_group_ref']['#prefix'] = '<div class="sbq_hide">';
    $form['og_group_ref']['#suffix'] = '</div>';

    $form['actions']['submit']['#value'] = '提交';
    $form['actions']['submit']['#attributes']['class'][] = 'sbq_btn';
    $form['actions']['#prefix'] = '<div class="sbq_botton_01"><label></label>';
    $form['actions']['#suffix'] = '</div>';
  } elseif ($form_id == 'answer_node_form') {
    $form['title']['#title'] = '我来帮他解答';
    $form['body']['und'][0]['#title'] = '我来帮他解答';
  } elseif ($form_id == 'privatemsg_list') {
    $form['#prefix'] = '<div class="sbq_pm_list"><div class="sbq_wrap"><div class="sbq_head">咨询管理</div>';
    $form['#suffix'] = '</div></div>';
    $form['updated']['actions']['#weight'] = '99';
  } elseif ($form_id == 'privatemsg_new') {
    $form['#prefix'] = '<div class="sbq_pm_editor">';
    $form['#suffix'] = '</div>';

    $form['body']['#rows'] = 1;
  }
}


function tiger_user_login_ajax_callback($form, $form_state) {
  global $user;
  $rtn = '';
  if ($user->uid) {
    $rtn = '<script type="text/javascript">
              parent.$.fn.colorbox.close();
              location.reload(true);
            </script>';
  } else {
    $rtn =  $form;
  }
  return $rtn;
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

function tiger_preprocess_user_picture(&$variables) {
  $variables['user_picture'] = '';
  if (variable_get('user_pictures', 0)) {
    $account = $variables['account'];
    if (!empty($account->picture)) {
      if (is_numeric($account->picture)) {
        $account->picture = file_load($account->picture);
      }
      if (!empty($account->picture->uri)) {
        $filepath = $account->picture->uri;
      }
    }
    elseif (variable_get('user_picture_default', '')) {
      $filepath = variable_get('user_picture_default', '');
    }
    if (isset($filepath)) {
      global $user;
      $alt = '';
      if ($account->uid == $user->uid && arg(1) != $user->uid) {
        $alt = t('返回我的主页');
      }

      if (module_exists('image') && file_valid_uri($filepath) && $style = variable_get('user_picture_style', '')) {
        $variables['user_picture'] = theme('image_style', array('style_name' => $style, 'path' => $filepath, 'alt' => $alt, 'title' => $alt));
      }
      else {
        $variables['user_picture'] = theme('image', array('path' => $filepath, 'alt' => $alt, 'title' => $alt));
      }
      if (!empty($account->uid) && user_access('access user profiles')) {
        $attributes = array('attributes' => array('title' => ''), 'html' => TRUE);
        $variables['user_picture'] = l($variables['user_picture'], "user/$account->uid", $attributes);
      }
    }
  }
}

function tiger_apachesolr_search_noresults() {
  return t('<div class="search-noresult"><ul>
<li>Check if your spelling is correct, or try removing filters.</li>
<li>Remove quotes around phrases to match each word individually: <em>"blue drop"</em> will match less than <em>blue drop</em>.</li>
<li>You can require or exclude terms using + and -: <em>big +blue drop</em> will require a match on <em>blue</em> while <em>big blue -drop</em> will exclude results that contain <em>drop</em>.</li>
</ul></div>');
}

function tiger_preprocess_privatemsg_view(&$vars) {
  global $user;
  $message = $vars['message'];
  $vars['self'] = FALSE;
  if ($user->uid == $message->author->uid) {
    $vars['self'] = TRUE;
  }
}

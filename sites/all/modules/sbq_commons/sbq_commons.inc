<?php

// 1.drupal load reply of comment by cid
//  give a cid ,load all it's comments
//  reference of comment_num_new() comment.module
//    http://drupal.stackexchange.com/questions/8582/how-to-show-node-comment-count-in-node-tpl
function sbq_comment_get_replys($pid) {
  return db_query('select cid as pid from comment where pid = :pid order by cid desc limit 0,3', array(
          ':pid' => $pid ))->fetchAll();
}

function sbq_comment_pager_reply($pid) {
  // this will be filled with an array of our content
  // $build = array();
  // // basic select query
  // $select = db_select('comment', 'c')
  //   ->fields('c', array('cid'))
  //   ->extend('PagerDefault') // this adds the pager
  //   ->condition('pid',$pid)
  //   ->limit(10);
  // // execute the query
  // $cids = $select->execute()->fetchCol();
  // // do something to output your results here.
  // foreach ($nids as $nid) {
  //   $content .= $nid;
  // }
  // // add the content
  // $build['content'] = array('#markup' => $content)
  // // Add the pager
  // $build['pager'] = array(
  //   '#theme' => 'pager',
  //   '#weight' => 5,
  // );
  // return the renderable array
  return $build;
}

function sbq_comment_print_comment($cid) {
  // $comment = comment_load($cid);
  // $comment = db_fetch_object(db_rewrite_sql(db_query('SELECT * FROM {comment} c WHERE c.cid = :pid', array(':pid' => $cid))
  // $sql = "SELECT * FROM {comment} c WHERE c.cid = %d";
  //  if ($comment = db_fetch_object(db_rewrite_sql(db_query($sql, $cid), 'c')) {
  //    return theme('comment__node_sbq_topic', $comment);
  //  }
  $comment = comment_load($cid);
  $account = user_load($comment->uid);
  //function rate_generate_widget($widget_id, $content_type, $content_id, $mode = RATE_FULL, $include_div = TRUE, $just_voted = FALSE, $displayed = NULL)
  $up_down = rate_generate_widget('1', 'comment', $cid, $mode = RATE_FULL, $include_div = TRUE, $just_voted = FALSE, $displayed = NULL);

  $comment_links = comment_links($comment, node_load($comment->nid));
  unset($comment_links['comment-reply']);
  $edit_link = '';
  // $edit_link = array(
  //     '#theme' => 'links__comment__comment',
  //     '#links' => $comment_links,
  //     '#attributes' => array('class' => array('links', 'inline')),
  // );
  // $edit_link = drupal_render($edit_link);

  return '<div class="views-row reply_comment_wrapper">

  <div class="views-field views-field-picture">        <div class="field-content">
  ' . theme('user_picture', array(
          'account' => $comment )) . '
</div>      </div>
  <div class="views-field views-field-name">
  <span class="field-content">
  ' . theme('username', array(
          'account' => $account )) . '
  </span>
  </div>
 ' . $edit_link . '
  <div class="views-field views-field-created">
    <span class="field-content">' . format_date($comment->created, $type = 'sbq_date_medium_revert', $format = '', $timezone = NULL, $langcode = NULL) . '
    </span>
  </div>
  <div class="views-field views-field-comment-body">        <div class="field-content">' . $comment->comment_body[LANGUAGE_NONE][0]['safe_value'] . '
</div>      </div>

</div>';
  // <div class="views-field views-field-value">
  //  <div class="field-content">'.render($up_down).'</div>
  // </div>
  // return theme('comment',$comment);
}

/**
 * print views item like comment for sbq
 */
function sbq_topic_views_comment_print($comment) {
  $account = user_load($comment->uid);
  $up_down = rate_generate_widget('1', 'comment', $comment->cid, $mode = RATE_FULL, $include_div = TRUE, $just_voted = FALSE, $displayed = NULL);

  return '<div class="views-row views-row-1 views-row-odd views-row-first views-row-last">

  <div class="views-field views-field-picture">        <div class="field-content"> ' . theme('user_picture', array(
          'account' => $comment )) . '
</div>
  </div>
  <div class="views-field views-field-name">        <span class="field-content">' . theme('username', array(
          'account' => $account )) . '</span>
  </div>
  <div class="views-field views-field-created">        <span class="field-content">' . format_date($comment->created, $type = 'sbq_date_medium_revert', $format = '', $timezone = NULL, $langcode = NULL) . '</span>
  </div>
  <div class="views-field views-field-comment-body">        <div class="field-content">' . $comment->subject . '
</div>
  </div>
  <div class="views-field views-field-cid">        <span class="field-content">129</span>
  </div>
  <div class="views-field views-field-value">        <div class="field-content"><div class="rate-widget-1 rate-widget clear-block rate-user rate-widget-yesno rate-processed"  disabled = "disabled"><ul><li class="first"><a disabled = "disabled" class="rate-button rate-yesno-btn disabled-a"  rel="nofollow" href="javascript:void(0);" title="您不可以支持自己">支持</a>0</li>
<li class="last"><a disabled = "disabled" class="rate-button rate-yesno-btn  disabled-a " id="rate-button-84" rel="nofollow" href="javascript:void(0);" title="您不可以反对自己">反对</a>0</li>
</ul></div></div>
  </div>
  <div class="views-field views-field-php">        <span class="field-content"><a href="javascript:void(0);" title="您不可以评论自己" class="sbv-show-cform  disabled-a" disabled = "disabled">评论(0)</a></span>
  </div>
       </div>';
}

/**
 * Builds the comment.
 */
function ajax_comments_submit_js4sbq($form, &$form_state) {
  // Return the actual form if it contains errors.
  if (form_get_errors()) {
    return $form;
  }

  // This is to remove the "Your comment has been posted" status message that
  // will appear upon refresh. This seems dirty but it means we don't have to
  // rewrite the whole comment_form_submit(). Please chime in if you think this
  // is dumb.
  ajax_comments_remove_status($_SESSION);

  $comment = $form_state['comment'];
  $node = $form['#node'];
  $notify_text = variable_get('ajax_comments_notify', '') ? theme('ajax_comments_notify_text') : '';

  $comment_build = comment_view($comment, $node);

  if (variable_get('comment_preview_' . $node->type)) {
    $commands[] = ajax_command_remove('.comment-preview');
    $commands[] = ajax_command_remove('.messages.ajax-comments.warning');
  }

  // Don't display as a preview as this is being submitted.
  unset($comment_build['comment_body']['#object']->in_preview);
// vote logic  for topic!
  $node = $form['#node'];
  $rate_widget_id = sbq_commons_get_rid_by_name('vote_sbq_topic');
  if ($rate_widget_id)
    $rate_result = rate_get_results('node', $node->nid, $rate_widget_id);

  if (isset($rate_result['user_vote'])) {
    $form['sbq_topic_voted'] = array(
        '#type' => 'hidden',
        '#value' => 0 );
    switch ($rate_result['user_vote']) {
      case '支持':
        $form['field_field_sbq_topic_type'][LANGUAGE_NONE]['#default_value'] = 1;
        $form['sbq_topic_voted'] = array(
            '#type' => 'hidden',
            '#value' => 1 );
        break;
      case '反对':
        $form['field_field_sbq_topic_type'][LANGUAGE_NONE]['#default_value'] = 0;
        $form['sbq_topic_voted'] = array(
            '#type' => 'hidden',
            '#value' => -1 );
        break;
      default:
        # code...
        break;
    }
  }
  $wrapper4sbq = 'sbq_topic_comments_reject';
  if ($form['sbq_topic_voted']['#value'] == 1) {
    $wrapper4sbq = 'sbq_topic_comments_approve';
  }
  if ($form['sbq_topic_voted']['#value'] == -1) {
    $wrapper4sbq = 'sbq_topic_comments_reject';
  }
  // Are we editing a comment.
  if (isset($form['cid']['#value'])) {
    // Remove wrapper because the form we replace exists inside the wrapper.
    unset($comment_build['#prefix']);
    unset($comment_build['#suffix']);

    // Trim surrounding whitespace so ajax.js doesn't wrap us in a new div.
    $comment_output = trim(drupal_render($comment_build));
    $commands[] = ajax_command_replace('#' . $form['#id'], $comment_output);
  }
  // Or are we replying to another comment.
  elseif (isset($form_state['values']['pid'])) {
    // Append comment to parent wrapper.
    $comment_output = drupal_render($comment_build);
    $commands[] = ajax_command_append('#comment-wrapper-' . $comment->pid, $notify_text . $comment_output);
    // Delete the form.
    $commands[] = ajax_command_invoke('#' . $form['#id'], 'remove');
  }
  // Or is this a brand new comment?
  else {
    // Append comment to root comment wrapper.
    $comment_output = drupal_render($comment_build);
    $commands[] = ajax_command_append('#comment-wrapper', $notify_text . $comment_output);
    $comment_output4sqb = sbq_topic_views_comment_print($comment);
    watchdog('wrapper4sbq', $wrapper4sbq, array(), WATCHDOG_NOTICE, 'link');
    $commands[] = ajax_command_prepend(".$wrapper4sbq .view-content", $comment_output4sqb);

    // If we have a default form, update it with a new one.
    if (variable_get('comment_form_location_' . $node->type, COMMENT_FORM_BELOW) == COMMENT_FORM_BELOW) {
      $node = $form['#node'];
      $new_form_state = array();
      $new_form_state['build_info']['args'][] = (object) array(
              'nid' => $node->nid );
      // Don't pull from cache.
      $new_form_state['input'] = array();
      $new_form_build = drupal_build_form($form['#form_id'], $new_form_state);
      $new_form_output = drupal_render($new_form_build);

      $commands[] = ajax_command_replace('#' . $form['#id'], $new_form_output);
    }
    // Otherwise, delete it.
    else {
      $commands[] = ajax_command_remove('#' . $form['#id']);
    }
  }

  return array(
      '#type' => 'ajax',
      '#commands' => $commands );
}

/**
 * Builds the comment.
 */
function ajax_comments_submit_js4child($form, &$form_state) {
  // Return the actual form if it contains errors.
  if (form_get_errors()) {
    return $form;
  }

  // This is to remove the "Your comment has been posted" status message that
  // will appear upon refresh. This seems dirty but it means we don't have to
  // rewrite the whole comment_form_submit(). Please chime in if you think this
  // is dumb.
  ajax_comments_remove_status($_SESSION);

  $comment = $form_state['comment'];
  $node = $form['#node'];
  $notify_text = variable_get('ajax_comments_notify', '') ? theme('ajax_comments_notify_text') : '';

  $comment_build = comment_view($comment, $node);

  if (variable_get('comment_preview_' . $node->type)) {
    $commands[] = ajax_command_remove('.comment-preview');
    $commands[] = ajax_command_remove('.messages.ajax-comments.warning');
  }

  // Don't display as a preview as this is being submitted.
  unset($comment_build['comment_body']['#object']->in_preview);

  // Are we editing a comment.
  if (isset($form['cid']['#value'])) {
    // Remove wrapper because the form we replace exists inside the wrapper.
    unset($comment_build['#prefix']);
    unset($comment_build['#suffix']);

    // Trim surrounding whitespace so ajax.js doesn't wrap us in a new div.
    $comment_output = trim(drupal_render($comment_build));
    $commands[] = ajax_command_replace('#' . $form['#id'], $comment_output);
  }
  // Or are we replying to another comment.
  elseif (isset($form_state['values']['pid'])) {
    // Append comment to parent wrapper.
    $comment_output = drupal_render($comment_build);
    $commands[] = ajax_command_append('#comment-wrapper-' . $comment->pid, $notify_text . $comment_output);

    $comment_replay_cotent = sbq_comment_print_comment($comment->cid);



    $commands[] = ajax_command_prepend('#sbq_topic_replay_warpper_' . $comment->pid, $comment_replay_cotent);

    // Delete the form.
    // $commands[] = ajax_command_invoke('#' . $form['#id'], 'remove');
    $node = $form['#node'];

    $new_form_state = array();
    $new_form_state['build_info']['args'][] = (object) array(
            'nid' => $node->nid,
            'pid' => $comment->pid );
    // Don't pull from cache.
    $new_form_state['input'] = array();
    $new_form_build = drupal_build_form($form['#form_id'], $new_form_state);
    $new_form_output = drupal_render($new_form_build);

    $commands[] = ajax_command_replace('#' . $form['#id'], $new_form_output);
  }
  // Or is this a brand new comment?
  else {
    // Append comment to root comment wrapper.
    $comment_output = drupal_render($comment_build);
    $commands[] = ajax_command_append('#comment-wrapper', $notify_text . $comment_output);
    // If we have a default form, update it with a new one.
    if (variable_get('comment_form_location_' . $node->type, COMMENT_FORM_BELOW) == COMMENT_FORM_BELOW) {
      $node = $form['#node'];
      $new_form_state = array();
      $new_form_state['build_info']['args'][] = (object) array(
              'nid' => $node->nid );
      // Don't pull from cache.
      $new_form_state['input'] = array();
      $new_form_build = drupal_build_form($form['#form_id'], $new_form_state);
      $new_form_output = drupal_render($new_form_build);
      $commands[] = ajax_command_replace('#' . $form['#id'], $new_form_output);
    }
    // Otherwise, delete it.
    else {
      $commands[] = ajax_command_remove('#' . $form['#id']);
    }
  }

  return array(
      '#type' => 'ajax',
      '#commands' => $commands );
}

function sbq_commons_modal_html($data, $id = 'sbq_modal', $title = '') {
  $html = '<div id="' . $id . '" class="modal fade in" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="false" style="display: block;">';
  $html .= '<div class="modal-dialog">';
  $html .= '<div class="modal-content">';
  $html .= '<div class="modal-header">';
  $html .= '<button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>';
  $html .= '<h4 class="modal-title" id="title">' . $title . '</h4>';
  $html .= '</div>';
  $html .= '<div class="modal-body">';
  $html .= $data;
  $html .= '</div>';
  $html .= '<div class="modal-footer">';
//  $html .= '<button type="button" class="btn btn-default" data-dismiss="modal">Close</button>';
//  $html .= '<button type="button" class="btn btn-primary">Save changes</button>';
  $html .= '</div>';
  $html .= '</div><!-- /.modal-content -->';
  $html .= '</div><!-- /.modal-dialog -->';
  $html .= '</div>';
  return $html;
}

/**
 * 登录失败3次 and 最近10分钟登录 跳出验证码
 * @see captcha_form_alter
 */
function _sbq_commons_captcha_display(&$form, &$form_alter, $form_id, $fail_times = 3, $mintue = 10) {
  $url = explode('/', $_GET['q']);
  if (isset($url[0]) && $url[0] == 'api') {
    return;
  }

  $pre_times = $fail_times - 1;
  $pre_ind = $fail_times - 2;
  // Visitor does not have permission to skip CAPTCHAs.
  module_load_include('inc', 'captcha');
  // Get CAPTCHA type and module for given form_id.
  $captcha_point = captcha_get_form_id_setting($form_id);

  if (!$captcha_point || !$captcha_point->captcha_type) {
    return;
  }
  if ($form_id == 'user_login_block' || $form_id == 'user_login') {
    $current_ip = ip_address();
    $fail_login = db_select('flood', 'f')
        ->fields('f')
        ->condition('event', 'failed_login_attempt_ip')
        ->condition('identifier', $current_ip)
        ->range(0, $fail_times)
        ->orderBy('timestamp', 'desc')
        ->execute();
    if ($fail_login->rowCount() < $pre_times) {
      return;
    }
    $result = $fail_login->fetchAll();
    $time_length = (time() - $result[$pre_ind]->timestamp) / 60;
    if ($time_length > $mintue) {
      return;
    }
  }

  // Build CAPTCHA form element.
  $captcha_element = array(
      '#type' => 'captcha',
      '#captcha_type' => $captcha_point->module . '/' . $captcha_point->captcha_type,
      '#weight' => 99,
  );
  // Add a CAPTCHA description if required.
  if (variable_get('captcha_add_captcha_description', TRUE)) {
    $captcha_element['#description'] = _captcha_get_description();
  }

  // Get placement in form and insert in form.
  $captcha_placement = _captcha_get_captcha_placement($form_id, $form);
  _captcha_insert_captcha_element($form, $captcha_placement, $captcha_element);
}

/**
 * Process relationship request.
 */
function sbq_commons_user_relationships_ui_pending_requested_ajax($viewer_id, $rid, $viewed_id, $action) {
  $user = user_load($viewer_id);
  $relationships = user_relationships_load(array(
      'rid' => $rid ), array(
      'include_user_info' => TRUE ));
  $relationship = $relationships[$rid];
  $requester = $relationship->requester;
  $requestee = $relationship->requestee;

  switch ($action) {
    case 'approve':
      if (!user_relationships_ui_check_access('approve', NULL, $relationship)) {
        drupal_access_denied();
        exit();
      }
      $relationship->approved = TRUE;
      user_relationships_save_relationship($relationship, $action);
      //drupal_set_message(user_relationships_get_message('accepted', $relationship));

      $html = sbq_commons_user_relationship_view(user_load($viewed_id), NULL, NULL);
      sbq_commons_ajax_response('success', 'success', NULL, render($html));
      break;

    case 'cancel':
      if (!user_relationships_ui_check_access('request', NULL, $relationship)) {
        drupal_access_denied();
        exit();
      }
      user_relationships_delete_relationship($relationship, $user, $form_state['values']['action']);
      //drupal_set_message(user_relationships_get_message($form_state['values']['action'], $relationship));

      break;

    case 'disapprove':
      if (!user_relationships_ui_check_access('approve', NULL, $relationship)) {
        drupal_access_denied();
        exit();
      }
      user_relationships_delete_relationship($relationship, $user, $form_state['values']['action']);
      // drupal_set_message(user_relationships_get_message($form_state['values']['action'], $relationship));
      $html = sbq_commons_user_relationship_view(user_load($viewed_id), NULL, NULL);
      sbq_commons_ajax_response('success', 'success', NULL, render($html));
      break;

    default:
      drupal_set_message(user_relationships_get_message('default'));
  }

  //$form_state['redirect'] = str_replace('destination=', '', drupal_get_destination());
}

function sbq_commons_user_relationship_view($account, $view_mode, $langcode) {
  global $user;
  if (($account->uid == $user->uid) && user_relationships_user_access('maintain @relationship relationships')) {
    _user_relationships_ui_set_notifications($account);
    return;
  }

  $output = array();
  if ($list = sbq_commons_relationships_ui_actions_between($user, $account, array(
      'remove' => 1 ))) {
    $output['relations'] = array(
        '#title' => t('Your relationships to this user'),
        '#type' => 'user_profile_item',
        '#markup' => theme('item_list', array(
            'items' => $list )),
        '#attributes' => array(
            'class' => array(
                'user_relationships_ui' ) ),
    );
  }
  if ($actions = sbq_commons_relationships_ui_actions_between($user, $account, array(
      'add' => 1,
      'requested' => 1,
      'received' => 1 ))) {
    $output['actions'] = array(
        '#title' => t('Relationship actions'),
        '#type' => 'user_profile_item',
        '#markup' => theme('item_list', array(
            'items' => $actions )),
        '#attributes' => array(
            'class' => array(
                'user_relationships_ui_actions' ) ),
    );
  }
  if (sizeof($output)) {
    $account->content['user_relationships_ui'] = array(
        '#type' => 'user_profile_category',
        '#title' => t('Relationships'),
        '#weight' => 10,
    );
    $account->content['user_relationships_ui'] = array_merge($account->content['user_relationships_ui'], $output);
    $account->content['user_relationships_ui']['#prefix'] = '<div id="sbq_commons_user_relationship_view">';
    $account->content['user_relationships_ui']['#suffix'] = '</div>';
  }
  return isset($account->content['user_relationships_ui']) ? $account->content['user_relationships_ui'] : '';
}

/*
 * response format
 */

function sbq_commons_ajax_response($status, $message, $data = '', $html = '') {
  $response = array(
      'status' => $status,
      'message' => $message,
      'data' => $data,
      'html' => $html,
  );
  die(json_encode($response));
}

function _sbq_commons_block_html($delta) {
  global $user;
  switch ($delta) {
    case 'sbq_user_profile':
      if (!$user->uid) {
        return;
      }
      $picture = sbq_commons_user_avart();
      //积分
      $list = userpoints_get_points_list();
      unset($list['actions']);
      $cpl = render($list);
      //操作
      $opt_link = l('操作', 'user/' . $user->uid . '/edit');
      $message_link = l('消息', 'messages');
      //勋章
      $user_badges = '';
      if (module_exists('user_badges')) {
        $user_badges = user_badges_for_uid($user->uid);
      }
      $block_html = <<<EOF
                   <i class="option">$opt_link</i>
                 <!--  <i class="message">$message_link</i> -->
                   <div id="sbq_picture">$picture</div>
                   <div id="sbq_name">$user->name</div>
                   $cpl
                   <div id="user_badges"><span>勋章</span><a href="/badges">$user_badges</a></div>
EOF;
      break;
    case 'sbq_quick_ask':
      if ($user->uid && arg(1)==$user->uid) {
        module_load_include('inc', 'node', 'node.pages');
        $node = (object) array(
                'uid' => $user->uid,
                'name' => (isset($user->name) ? $user->name : ''),
                'type' => 'question',
                'language' => LANGUAGE_NONE
        );
        $question_node_form = drupal_get_form('question_node_form', $node);
        $block_html = '<div class="sbq-question-node-add-form">'
            . '<div class="sbq-user-add-post">' . l('发布文章', 'node/add/blog') . '</div>'
            . render($question_node_form)
            . '</div>';
      }
      break;
    case 'sbq_add_ask_link':
      if (!$user->uid) {
        return;
      }
      $block_html = '<div class="sbq-user-add-question">' . l('我要提问', 'node/add/question') . '</div>';
      break;

    case 'sbq_user_menu':
      if (!$user->uid) {
        return;
      }
      $relationship_li_active = '';
      $relationship_link_active = '';
      $points_li_active = '';
      $points_link_active = '';
      if (arg(2) == 'relationship') {
        $relationship_li_active = ' active';
        $relationship_link_active = ' is-active active';
      }
      if (arg(2) == 'points') {
        $points_li_active = ' active';
        $points_link_active = ' is-active active';
      }
      $user_post_count = sbq_commons_get_count($user->uid, 'post');
      $user_message_count = sbq_commons_messages_count($user);
      $user_blog_count = sbq_commons_get_count($user->uid, 'blog');
      $user_qa_count = sbq_commons_get_count($user->uid, 'question') + sbq_commons_get_count($user->uid, 'answer');
      ;

      //$user_group_count = 0;
      $user_relationship_count = sbq_user_relationships_my_relstionships($user);
      $user_point_count = userpoints_get_current_points($user->uid, 'all');

      $block_html = '<div class="sbq-user-menu">'
          . '<ul class="menu nav">'
          . '<li class="menu__item is-leaf first leaf sbq-user-menu-post">'
          . '<a href="/user/' . $user->uid . '#block-quicktabs-user-group" class="menu__link">我的问答</a>'
          . '<span class="sbq-count"><a href="#" class="sbq-count-link">' . $user_qa_count . '条</a></span></li>'

          // . '<li class="menu__item is-leaf first leaf sbq-user-menu-post">'
          // . '<a href="/user/' . $user->uid . '#block-quicktabs-user-group" class="menu__link">我的帖子</a>'
          // . '<span class="sbq-count"><a href="#" class="sbq-count-link">' . $user_post_count . '条</a></span></li>'
          . '<li class="menu__item is-leaf leaf sbq-user-menu-status"><a href="/user/' . $user->uid . '#block-quicktabs-message" class="menu__link">好友动态</a><span class="sbq-count"><a href="#" class="sbq-count-link">' . $user_message_count . '条</a></span></li>'
          . '<li class="menu__item is-leaf leaf sbq-user-menu-blog"><a href="/user/' . $user->uid . '#block-views-blog-my-blog-block" class="menu__link">我的文章</a><span class="sbq-count"><a href="#" class="sbq-count-link">' . $user_blog_count . '篇</a></span></li>'
          //. '<li class="menu__item is-leaf leaf sbq-user-menu-group"><a href="/groups/my" class="menu__link">我的小组</a><span class="sbq-count"><a href="#" class="sbq-count-link">5个</a></span></li>'
          . '<li class="menu__item is-leaf last leaf sbq-user-menu-relationship' . $relationship_li_active . '"><a href="/user/' . $user->uid . '/relationship" class="menu__link' . $relationship_link_active . '">我的圈子</a><span class="sbq-count"><a href="#" class="sbq-count-link">' . $user_relationship_count . '人</a></span></li>'
          // . '<li class="menu__item is-leaf last leaf sbq-user-menu-points' . $points_li_active . '"><a href="/user/' . $user->uid . '/points" class="menu__link' . $points_link_active . '">我的积分</a><span class="sbq-count"><a href="#" class="sbq-count-link">' . $user_point_count . '</a></span></li>'
          . '</ul>'
          . '</div>';
      break;
    case 'recommond_doctors':
      $ids = _sbq_commons_user_recommonds_friends_ids(USER_CERTIFIED_DOCTOR_RID);
      $friends = user_load_multiple($ids);
      $block_html = '<div class="view"> <div class="view-content">';
      foreach ($friends as $value) {
        $relatioships = sbq_user_relationships_action_between_user($user, $value);
        $relatioships = reset($relatioships);
        $accounts_view = array(
            'user' => user_load($value->uid),
            'relationship_type' => $relatioships['relationship_type'],
            'relstionship_action' => $relatioships['relationship_action'],
        );
        $block_html .= sbq_user_relationships_profile($accounts_view);
      }
      if ($block_html) {
        $block_html .= '</div><div class="more-link"><a href="/user/' . $user->uid . '/relationship/recommand/doctor">更多</a></div></div>';
      }
      break;
    case 'recommond_patients':
      if (!$user->uid) {
        return;
      }
      $ids = _sbq_commons_user_recommonds_friends_ids(USER_PATIENT_RID);
      $friends = user_load_multiple($ids);
      $block_html = '<div class="view"> <div class="view-content">';
      foreach ($friends as $value) {
        $relatioships = sbq_user_relationships_action_between_user($user, $value);
        $relatioships = reset($relatioships);
        $accounts_view = array(
            'user' => user_load($value->uid),
            'relationship_type' => $relatioships['relationship_type'],
            'relstionship_action' => $relatioships['relationship_action'],
        );
        $block_html .= sbq_user_relationships_profile($accounts_view);
      }
      if ($block_html) {
        $block_html .= '</div><div class="more-link"><a href="/user/' . $user->uid . '/relationship/recommand/patient">更多</a></div></div>';
      }
      break;
    case 'app_page':
      drupal_add_css(drupal_get_path('module', 'sbq_commons') . '/css/app-download.css');
      $block_html = '<div class="second-code">'
          . '<h2>扫描二维码 即可下载应用</h2>'
          . '<image src="http://app.shangbq.com/res/api.png">'
          . '</div>'
          . '<iframe width="270" height="550" class="share_self"  frameborder="0" scrolling="no" src="http://widget.weibo.com/weiboshow/index.php?language=&width=270&height=550&fansRow=2&ptype=1&speed=0&skin=1&isTitle=1&noborder=1&isWeibo=1&isFans=1&uid=3910809638&verifier=480ee660&dpc=1"></iframe>';

      break;
    default:
      break;
  }
  return isset($block_html) ? $block_html : '';
}

function _sbq_commons_user_recommonds_friends_ids($roles, $num = 2, $account = null) {
  if (!$account) {
    global $user;
    $account = $user;
  }
  $query_user = db_query(
      "select uid from {users} u where " .
      "u.uid not in ( select requestee_id from user_relationships " .
      "where requester_id = {$account->uid}) " .
      "and u.uid not in( select requester_id from user_relationships where requestee_id = {$account->uid}) " .
      "and u.uid <> {$account->uid} ".
      "and u.uid in ( select uid from users_roles where rid = {$roles}) order by uid asc limit 0,{$num}");
  $result = $query_user->fetchAllAssoc('uid');

  return $result ? array_keys($result) : array();
}

/*
 * Add Disease tags for User Center
 */

function sbq_commons_user_disease_tag_add_ajax($tag_name = '') {
  global $user;
  $li_html = '';

  if (strlen(trim($tag_name)) > 0 && $user->uid > 0) {
    //get term id by name
    $vocabulary = taxonomy_vocabulary_machine_name_load('diseases');
    $v_name = $vocabulary->machine_name;
    $term = taxonomy_get_term_by_name($tag_name, $v_name);

    //if term not found, create
    $count = count($term);
    if ($count == 0) {
      $term = new stdClass();
      $term->name = $tag_name;
      $term->vid = $vocabulary->vid;
      taxonomy_term_save($term);
      $tid = $term->tid;
    } else {
      foreach ($term as $key => $value) {
        $tid = $value->tid;
      }
    }

    $profile = profile2_load_by_user($user->uid, 'main');
    if (!$profile) {
      // if profile is empty, create for this user
      $profile = profile2_create(array( 'type' => 'main', 'uid' => $user->uid ));
    }
    $index = count($profile->field_tags_disease['und']);
    $checked = FALSE;
    foreach ($profile->field_tags_disease['und'] as $key => $value) {
      if ($value['tid'] == $tid) {
        $checked = TRUE;
      }
    }

    if (!$checked) {
      $profile->field_tags_disease['und'][$index] = array(
          'tid' => $tid );
      profile2_save($profile);
      $li_html = '<li>'
          . '<a href="#" typeof="skos:Concept" property="rdfs:label skos:prefLabel" datatype="">' . $tag_name . '</a>'
          . '<span class="sba-user-tag-del">'
          . '<a href="/user/ajax/tags/' . $tid . '/delete">-</a>'
          . '</span>'
          . '</li>';
    }
  }

  $commands = array();
  $commands[] = ajax_command_replace(NULL, $li_html);
  $page = array(
      '#type' => 'ajax',
      '#commands' => $commands );
  ajax_deliver($page);
}

/*
 * Delete Disease tags for User Center
 */

function sbq_commons_user_disease_tag_delete_ajax($tid = 0) {
  global $user;

  if ($tid > 0 && $user->uid > 0) {
    //unset term from the user
    $profile = profile2_load_by_user($user->uid, 'main');
    foreach ($profile->field_tags_disease['und'] as $key => $value) {
      if ($value['tid'] == $tid) {
        $delete_key = $key;
      }
    }
    unset($profile->field_tags_disease['und'][$delete_key]);
    profile2_save($profile);
  }

  $commands = array();
  $commands[] = ajax_command_replace(NULL, theme('status_messages'));
  $page = array(
      '#type' => 'ajax',
      '#commands' => $commands );
  ajax_deliver($page);
}

/**
 * QA index page
 * return empty page for zen_kh theme
 * Use tabs blocks to theme this page
 */
function druedu_qa_empty_page() {
  return '';
}

/*
 *
 */

function sbq_commons_app_down() {

  return theme('app_dowunload');
}

/*
 * get node count by user and type
 */

function sbq_commons_get_count($uid = 0, $type = '') {
  $rtn = 0;
  if ($uid > 0 && strlen(trim($type)) > 0) {
    $rtn = db_query('SELECT count(nid) FROM {node} WHERE uid = :uid AND type = :type', array(
        ':uid' => $uid,
        ':type' => $type ))->fetchCol();
  }
  return $rtn[0];
}

/*
 * ajax_quick_ask_callback
 */

function ajax_quick_ask_callback($form, &$form_state) {
  $body = $form_state['input']['body']['und'][0]['value'];
  if (isset($body) && strlen(trim($body)) > 0) {
    # code...
    $commands = array();
    module_load_include('inc', 'node', 'node.pages');
    $node = node_form_submit_build_node($form, $form_state);
    $insert = empty($node->nid);
    node_save($node);
    $node_link = l(t('view'), 'node/' . $node->nid);
    $watchdog_args = array(
        '@type' => $node->type,
        '%title' => $node->title,
    );

    if ($insert) {
      watchdog('content', '@type: added %title.', $watchdog_args, WATCHDOG_NOTICE, $node_link);
    }
    if ($node->nid) {
      $form_state['values']['nid'] = $node->nid;
      $form_state['nid'] = $node->nid;
      $title = l($node->title, 'node/' . $node->nid);
      $str_date = format_date(time(), 'custom', 'Y-m-d');
      $nqs = '<div class="views-row views-row-1 views-row-odd views-row-first">'
          . '<div class="views-field views-field-title"><span class="field-content">' . $title . '</span></div>'
          . '<div class="views-field views-field-value"><span class="field-content">0</span></div>'
          . '<div class="views-field views-field-field-mark-question-resolved"><div class="field-content">未解决</div></div>'
          . '<div class="views-field views-field-created"><span class="field-content">' . $str_date . '</span></div></div>';
      $new_textarea = '<textarea class="text-full ckeditor-mod form-textarea" id="edit-body-und-0-value" name="body[und][0][value]" cols="60" rows="20"></textarea>';
      $commands[] = ajax_command_replace('#edit-body-und-0-value', $new_textarea);
      $commands[] = ajax_command_prepend('#block-views-my-qa-my-ask .view-content', $nqs);
      $commands[] = ajax_command_replace('#sbq-message-error', '');
    } else {
      // In the unlikely case something went wrong on save, the node will be
      // rebuilt and node form redisplayed the same way as in preview.
      drupal_set_message(t('The post could not be saved.'), 'error');
      $form_state['rebuild'] = TRUE;
    }
  } else {
    $error_msg = '<div id="sbq-message-error" class="messages--error messages error">'
        . '<h2 class="element-invisible">错误信息</h2>'
        . '<ul class="messages__list">'
        . '<li class="messages__item">请输入您的问题</li>'
        . '</ul></div>';
    $commands[] = ajax_command_after('#main-content', $error_msg);
    $form_state['rebuild'] = TRUE;
  }

  $page = array(
      '#type' => 'ajax',
      '#commands' => $commands );
  ajax_deliver($page);
}

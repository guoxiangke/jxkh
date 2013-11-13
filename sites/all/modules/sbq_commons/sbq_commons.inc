<?php

// 1.drupal load reply of comment by cid
//  give a cid ,load all it's comments
//  reference of comment_num_new() comment.module
//    http://drupal.stackexchange.com/questions/8582/how-to-show-node-comment-count-in-node-tpl
function sbq_comment_get_replys($pid) {
    return db_query('select cid as pid from comment where pid = :pid order by cid desc limit 0,3', array(
                ':pid' => $pid))->fetchAll();
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
    $comment     = comment_load($cid);
    $account     = user_load($comment->uid);
    //function rate_generate_widget($widget_id, $content_type, $content_id, $mode = RATE_FULL, $include_div = TRUE, $just_voted = FALSE, $displayed = NULL)
    $up_down     = rate_generate_widget('1', 'comment', $cid, $mode        = RATE_FULL, $include_div = TRUE, $just_voted  = FALSE, $displayed   = NULL);

    $comment_links = comment_links($comment, node_load($comment->nid));
    unset($comment_links['comment-reply']);
    $edit_link     = '';
    // $edit_link = array(
    //     '#theme' => 'links__comment__comment',
    //     '#links' => $comment_links,
    //     '#attributes' => array('class' => array('links', 'inline')),
    // );
    // $edit_link = drupal_render($edit_link);

    return '<div class="views-row reply_comment_wrapper">

  <div class="views-field views-field-picture">        <div class="field-content">
  ' . theme('user_picture', array(
                'account' => $comment)) . '
</div>      </div>
  <div class="views-field views-field-name">
  <span class="field-content">
  ' . theme('username', array(
                'account' => $account)) . '
  </span>
  </div>
 ' . $edit_link . '
  <div class="views-field views-field-created">
    <span class="field-content">' . format_date($comment->created, $type     = 'sbq_date_medium_revert', $format   = '', $timezone = NULL, $langcode = NULL) . '
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
    $account     = user_load($comment->uid);
    $up_down     = rate_generate_widget('1', 'comment', $comment->cid, $mode        = RATE_FULL, $include_div = TRUE, $just_voted  = FALSE, $displayed   = NULL);

    return '<div class="views-row views-row-1 views-row-odd views-row-first views-row-last">

  <div class="views-field views-field-picture">        <div class="field-content"> ' . theme('user_picture', array(
                'account' => $comment)) . '
</div>
  </div>
  <div class="views-field views-field-name">        <span class="field-content">' . theme('username', array(
                'account' => $account)) . '</span>
  </div>
  <div class="views-field views-field-created">        <span class="field-content">' . format_date($comment->created, $type     = 'sbq_date_medium_revert', $format   = '', $timezone = NULL, $langcode = NULL) . '</span>
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

    $comment     = $form_state['comment'];
    $node        = $form['#node'];
    $notify_text = variable_get('ajax_comments_notify', '') ? theme('ajax_comments_notify_text') : '';

    $comment_build = comment_view($comment, $node);

    if (variable_get('comment_preview_' . $node->type)) {
        $commands[] = ajax_command_remove('.comment-preview');
        $commands[] = ajax_command_remove('.messages.ajax-comments.warning');
    }

    // Don't display as a preview as this is being submitted.
    unset($comment_build['comment_body']['#object']->in_preview);
// vote logic  for topic!
    $node           = $form['#node'];
    $rate_widget_id = sbq_commons_get_rid_by_name('vote_sbq_topic');
    if ($rate_widget_id)
        $rate_result    = rate_get_results('node', $node->nid, $rate_widget_id);

    if (isset($rate_result['user_vote'])) {
        $form['sbq_topic_voted'] = array(
            '#type' => 'hidden',
            '#value' => 0);
        switch ($rate_result['user_vote']) {
            case '支持':
                $form['field_field_sbq_topic_type'][LANGUAGE_NONE]['#default_value'] = 1;
                $form['sbq_topic_voted']                                             = array(
                    '#type' => 'hidden',
                    '#value' => 1);
                break;
            case '反对':
                $form['field_field_sbq_topic_type'][LANGUAGE_NONE]['#default_value'] = 0;
                $form['sbq_topic_voted']                                             = array(
                    '#type' => 'hidden',
                    '#value' => -1);
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
        $commands[]     = ajax_command_replace('#' . $form['#id'], $comment_output);
    }
    // Or are we replying to another comment.
    elseif (isset($form_state['values']['pid'])) {
        // Append comment to parent wrapper.
        $comment_output = drupal_render($comment_build);
        $commands[]     = ajax_command_append('#comment-wrapper-' . $comment->pid, $notify_text . $comment_output);
        // Delete the form.
        $commands[]     = ajax_command_invoke('#' . $form['#id'], 'remove');
    }
    // Or is this a brand new comment?
    else {
        // Append comment to root comment wrapper.
        $comment_output     = drupal_render($comment_build);
        $commands[]         = ajax_command_append('#comment-wrapper', $notify_text . $comment_output);
        $comment_output4sqb = sbq_topic_views_comment_print($comment);
        watchdog('wrapper4sbq', $wrapper4sbq, array(), WATCHDOG_NOTICE, 'link');
        $commands[]         = ajax_command_prepend(".$wrapper4sbq .view-content", $comment_output4sqb);

        // If we have a default form, update it with a new one.
        if (variable_get('comment_form_location_' . $node->type, COMMENT_FORM_BELOW) == COMMENT_FORM_BELOW) {
            $node                                   = $form['#node'];
            $new_form_state                         = array();
            $new_form_state['build_info']['args'][] = (object) array(
                        'nid' => $node->nid);
            // Don't pull from cache.
            $new_form_state['input']                = array();
            $new_form_build                         = drupal_build_form($form['#form_id'], $new_form_state);
            $new_form_output                        = drupal_render($new_form_build);

            $commands[] = ajax_command_replace('#' . $form['#id'], $new_form_output);
        }
        // Otherwise, delete it.
        else {
            $commands[] = ajax_command_remove('#' . $form['#id']);
        }
    }

    return array(
        '#type' => 'ajax',
        '#commands' => $commands);
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

    $comment     = $form_state['comment'];
    $node        = $form['#node'];
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
        $commands[]     = ajax_command_replace('#' . $form['#id'], $comment_output);
    }
    // Or are we replying to another comment.
    elseif (isset($form_state['values']['pid'])) {
        // Append comment to parent wrapper.
        $comment_output = drupal_render($comment_build);
        $commands[]     = ajax_command_append('#comment-wrapper-' . $comment->pid, $notify_text . $comment_output);

        $comment_replay_cotent = sbq_comment_print_comment($comment->cid);



        $commands[] = ajax_command_prepend('#sbq_topic_replay_warpper_' . $comment->pid, $comment_replay_cotent);

        // Delete the form.
        // $commands[] = ajax_command_invoke('#' . $form['#id'], 'remove');
        $node = $form['#node'];

        $new_form_state                         = array();
        $new_form_state['build_info']['args'][] = (object) array(
                    'nid' => $node->nid,
                    'pid' => $comment->pid);
        // Don't pull from cache.
        $new_form_state['input']                = array();
        $new_form_build                         = drupal_build_form($form['#form_id'], $new_form_state);
        $new_form_output                        = drupal_render($new_form_build);

        $commands[] = ajax_command_replace('#' . $form['#id'], $new_form_output);
    }
    // Or is this a brand new comment?
    else {
        // Append comment to root comment wrapper.
        $comment_output = drupal_render($comment_build);
        $commands[]     = ajax_command_append('#comment-wrapper', $notify_text . $comment_output);

        // If we have a default form, update it with a new one.
        if (variable_get('comment_form_location_' . $node->type, COMMENT_FORM_BELOW) == COMMENT_FORM_BELOW) {
            $node = $form['#node'];

            $new_form_state                         = array();
            $new_form_state['build_info']['args'][] = (object) array(
                        'nid' => $node->nid);
            // Don't pull from cache.
            $new_form_state['input']                = array();
            $new_form_build                         = drupal_build_form($form['#form_id'], $new_form_state);
            $new_form_output                        = drupal_render($new_form_build);

            $commands[] = ajax_command_replace('#' . $form['#id'], $new_form_output);
        }
        // Otherwise, delete it.
        else {
            $commands[] = ajax_command_remove('#' . $form['#id']);
        }
    }

    return array(
        '#type' => 'ajax',
        '#commands' => $commands);
}

function sbq_commons_modal_html($data, $id = 'sbq_modal', $title = '') {


    $html = '<div id="' . $id . '" class="modal fade in" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="false" style="display: block;">';
    $html .= '<div class="modal-dialog">';
    $html .= '<div class="modal-content">';
    $html .= '<div class="modal-header">';
    $html .= '<button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>';
    $html .= '<h4 class="modal-title" id="' . $$data . 'Label">' . $title . '</h4>';
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
    $pre_times     = $fail_times - 1;
    $pre_ind       = $fail_times - 2;
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
            //drupal_rebuild_form($form_id, $form_state);
            return;
        }
        $result      = $fail_login->fetchAll();
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
 * Remove relationship request.
 */
function sbq_commons_user_relationships_ui_remove_ajax($viewer_id, $rid, $viewd_id) {
    $user         = user_load($viewer_id);
    $relationship = user_relationships_load($rid);
    if (!user_relationships_ui_check_access('delete', NULL, $relationship)) {
        drupal_access_denied();
        exit();
    }
    if (!user_relationships_load($rid)) {
        sbq_commons_ajax_response('success', '找不到此关系！', NULL, render($html));
    }
    user_relationships_delete_relationship($relationship, $user);
    drupal_set_message(user_relationships_get_message('removed', $relationship));
    $html = sbq_commons_user_relationship_view(user_load($viewd_id), NULL, NULL);
    sbq_commons_ajax_response('success', 'success', NULL, render($html));
}

/**
 * Process relationship request.
 */
function sbq_commons_user_relationships_ui_request_ajax($viewer_id, $rid, $viewed_id) {
    //#578372 leave all form values in the object for other functions to use
    $relationship            = new stdClass;
    $relationship->requester = user_load($viewer_id);
    $relationship->requestee = user_load($viewed_id);
    $relationship->type      = user_relationships_type_load($rid);
    $relationship            = user_relationships_request_relationship($relationship);
    if ($relationship === FALSE || !$relationship) {
        sbq_commons_ajax_response('success', '不能建立此关系', NULL, render($html));
    }
    //  drupal_set_message(user_relationships_get_message(($relationship->approved ? 'pre_approved' : 'submitted'), $relationship));
    $html = sbq_commons_user_relationship_view(user_load($viewed_id), NULL, NULL);
    sbq_commons_ajax_response('success', 'success', NULL, render($html));
}

/**
 * Process relationship request.
 */
function sbq_commons_user_relationships_ui_pending_requested_ajax($viewer_id, $rid, $viewed_id, $action) {
    $user          = user_load($viewer_id);
    $relationships = user_relationships_load(array(
        'rid' => $rid), array(
        'include_user_info' => TRUE));
    $relationship  = $relationships[$rid];
    $requester     = $relationship->requester;
    $requestee     = $relationship->requestee;

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
    if ($list   = sbq_commons_relationships_ui_actions_between($user, $account, array(
        'remove' => 1))) {
        $output['relations'] = array(
            '#title' => t('Your relationships to this user'),
            '#type' => 'user_profile_item',
            '#markup' => theme('item_list', array(
                'items' => $list)),
            '#attributes' => array(
                'class' => array(
                    'user_relationships_ui')),
        );
    }
    if ($actions = sbq_commons_relationships_ui_actions_between($user, $account, array(
        'add' => 1,
        'requested' => 1,
        'received' => 1))) {
        $output['actions'] = array(
            '#title' => t('Relationship actions'),
            '#type' => 'user_profile_item',
            '#markup' => theme('item_list', array(
                'items' => $actions)),
            '#attributes' => array(
                'class' => array(
                    'user_relationships_ui_actions')),
        );
    }
    if (sizeof($output)) {
        $account->content['user_relationships_ui']            = array(
            '#type' => 'user_profile_category',
            '#title' => t('Relationships'),
            '#weight' => 10,
        );
        $account->content['user_relationships_ui']            = array_merge($account->content['user_relationships_ui'], $output);
        $account->content['user_relationships_ui']['#prefix'] = '<div id="sbq_commons_user_relationship_view">';
        $account->content['user_relationships_ui']['#suffix'] = '</div>';
    }
    return isset($account->content['user_relationships_ui']) ? $account->content['user_relationships_ui'] : '';
}

/*
 * response format
 */

function sbq_commons_ajax_response($status, $message, $data, $html) {
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
            $account = user_load($user->uid);
            if (isset($account->picture->uri)) {
                $image   = $account->picture->uri;
                $picture = theme('image_style', array(
                    'path' => $image,
                    'style_name' => 'sc80',
                ));
            } else {
                $default_image_uri = variable_get('user_picture_default');
                $image             = file_create_url($default_image_uri);
                $picture           = theme('image_style', array(
                    'path' => $default_image_uri,
                    'style_name' => 'sc80',
                ));
            }
            //积分
            $list         = userpoints_get_points_list();
            $cpl          = render($list);
            //操作
            $opt_link     = l('操作', 'user/');
            $message_link = l('消息', 'user/');
            //勋章
            $user_badges  = '';
            if (module_exists('user_badges')) {
                $user_badges = user_badges_for_uid($user->uid);
            }
            $block_html = <<<EOF
                   <i class="option">$opt_link</i>
                   <i class="message">$message_link</i>
                   <div id="sbq_picture">$picture</div>
                   <div id="sbq_name">$user->name</div>
                   $cpl
                   <div id="user_badges"><span>勋章</span>$user_badges</div>
EOF;
            break;
        case 'sbq_quick_ask':
            if (!$user->uid) {
                return;
            }
            module_load_include('inc', 'node', 'node.pages');
            $node               = (object) array(
                        'uid' => $user->uid,
                        'name' => (isset($user->name) ? $user->name : ''),
                        'type' => 'question',
                        'language' => LANGUAGE_NONE);
            $question_node_form = drupal_get_form('question_node_form', $node);

            $question_node_form['field_tags']['und']['#value'] = '快速提问';
            $question_node_form['field_tags']['#type']         = 'hidden';
            unset($question_node_form['body']['und']['0']['format']);
            unset($question_node_form['body']['und']['0']['summary']);
            unset($question_node_form['field_departments']);

            $block_html = '<div class="sbq-question-node-add-form">'
                    . render($question_node_form)
                    . '</div>';
            break;

        case 'sbq_user_menu':
            if (!$user->uid) {
                return;
            }

            $block_html = '<div class="sbq-user-menu">'
                    . '<ul class="menu">'
                    . '<li class="menu__item is-leaf first leaf sbq-user-menu-post"><a href="#" class="menu__link">我的帖子</a></li>'
                    . '<li class="menu__item is-leaf leaf sbq-user-menu-status"><a href="#" class="menu__link">我的动态</a></li>'
                    . '<li class="menu__item is-leaf leaf sbq-user-menu-blog"><a href="#" class="menu__link">我的文章</a></li>'
                    . '<li class="menu__item is-leaf leaf sbq-user-menu-group"><a href="#" class="menu__link">我的小组</a></li>'
                    . '<li class="menu__item is-leaf last leaf sbq-user-menu-relationship"><a href="#" class="menu__link">我的圈子</a></li>'
                    . '</ul>'
                    . '</div>';
            break;

        default:
            break;
    }
    return isset($block_html) ? $block_html : '';
}

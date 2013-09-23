<?php

// 1.drupal load reply of comment by cid
//  give a cid ,load all it's comments
//  reference of comment_num_new() comment.module
//    http://drupal.stackexchange.com/questions/8582/how-to-show-node-comment-count-in-node-tpl
function sbq_comment_get_replys($pid) {
  return db_query('select cid as pid from comment where pid = :pid order by cid desc limit 0,3', array(':pid' => $pid))->fetchAll();
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
  ' . theme('user_picture', array('account' => $comment)) . '
</div>      </div>  
  <div class="views-field views-field-name">
  <span class="field-content">
  ' . theme('username', array('account' => $account)) . '
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
      
  <div class="views-field views-field-picture">        <div class="field-content"> ' . theme('user_picture', array('account' => $comment)) . '
</div>
  </div>  
  <div class="views-field views-field-name">        <span class="field-content">' . theme('username', array('account' => $account)) . '</span>
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
    $form['sbq_topic_voted'] = array('#type' => 'hidden', '#value' => 0);
    switch ($rate_result['user_vote']) {
      case '支持':
        $form['field_field_sbq_topic_type'][LANGUAGE_NONE]['#default_value'] = 1;
        $form['sbq_topic_voted'] = array('#type' => 'hidden', '#value' => 1);
        break;
      case '反对':
        $form['field_field_sbq_topic_type'][LANGUAGE_NONE]['#default_value'] = 0;
        $form['sbq_topic_voted'] = array('#type' => 'hidden', '#value' => -1);
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
      $new_form_state['build_info']['args'][] = (object) array('nid' => $node->nid);
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

  return array('#type' => 'ajax', '#commands' => $commands);
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

    watchdog('CID', $comment->cid, array(), WATCHDOG_NOTICE, 'link');

    $comment_replay_cotent = sbq_comment_print_comment($comment->cid);



    $commands[] = ajax_command_prepend('#sbq_topic_replay_warpper_' . $comment->pid, $comment_replay_cotent);

    // Delete the form.
    // $commands[] = ajax_command_invoke('#' . $form['#id'], 'remove');
    // $commands[] = ajax_command_invoke('#' . $form['#id'], 'emptyTextarea');
      $node = $form['#node'];

      $new_form_state = array();
      $new_form_state['build_info']['args'][] = (object) array('nid' => $node->nid, 'pid' => $comment->pid);
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
      $new_form_state['build_info']['args'][] = (object) array('nid' => $node->nid);
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

  return array('#type' => 'ajax', '#commands' => $commands);
}
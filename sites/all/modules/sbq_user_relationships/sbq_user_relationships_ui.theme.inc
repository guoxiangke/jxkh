<?php

/**
 * @file
 * User Relationships theme-able functions
 */

/**
 * Show the current status of a relationship
 */
function theme_sbq_user_relationships_approval_status($variables) {
  $approved = $variables['approved'];
  return isset($approved) ? ($approved ? t('Approved') : t('Not Approved')) : t('Unknown');
}

/**
 * Create relationship link
 */
function theme_sbq_user_relationships_request_relationship_link($variables) {
  $relate_to = $variables['relate_to'];
  return l(
      t('Create a relationship with %name', array( '%name' => format_username($relate_to) )), "relationship/{$relate_to->uid}/request", array(
      'query' => drupal_get_destination(),
      'html' => TRUE,
      )
  );
}

/**
 * Create a direct relationship link
 */
function theme_sbq_user_relationships_request_relationship_direct_link($variables) {
  $relate_to = $variables['relate_to'];
  $relationship_type = $variables['relationship_type'];
  //safety, revert to  a generic link
  if (!isset($relationship_type)) {
    return theme('user_relationships_request_relationship_link', array( 'relate_to' => $relate_to ));
  }
  return l(
      t("Become %name's @rel_name", array( '%name' => format_username($relate_to) ) + user_relationships_type_translations($relationship_type)), "relationship/{$relate_to->uid}/request/{$relationship_type->rtid}", array(
      'query' => drupal_get_destination(),
      'html' => TRUE,
      'attributes' => array( 'class' => array( 'user_relationships_popup_link' ) ),
      )
  );
}

/**
 * Remove relationship link
 */
function theme_sbq_user_relationships_remove_link($variables) {
  $uid = $variables['uid'];
  $rid = $variables['rid'];
  $vid = $variables['vid'];
  $ajax_token = 'user_relationships_remove' . $vid;

  return l(t('-移除'), "relationship/ajax/{$uid}/remove/{$rid}/$vid?destination=$ajax_token", array(
      'attributes' => array(
          'class' => array(
              'class' => 'use-ajax ' . $ajax_token
          )
      )
      )
  );
}

/**
 * Approve to pending relationship link
 */
function theme_sbq_user_relationships_pending_request_approve_link($variables) {
  $uid = $variables['uid'];
  $rid = $variables['rid'];
  $vid = $variables['vid'];
  return l(
      t('同意'), "user/{$uid}/relationship/action/{$rid}/approve", array(
      'query' => array( 'destination' => 'pending_request_approve_link' . $vid ),
      'attributes' => array( 'class' => array( 'use-ajax pending_request_approve_link arrpove' . $vid ) ),
      )
  );
}

/**
 * Decline to pending relationship link
 */
function theme_sbq_user_relationships_pending_request_disapprove_link($variables) {
  $uid = $variables['uid'];
  $rid = $variables['rid'];
  $vid = $variables['vid'];
  return l(
      t('拒绝'), "user/{$uid}/relationship/action/{$rid}/disapprove", array(
      'query' => array( 'destination' => 'pending_request_disapprove_link' . $vid ),
      'attributes' => array( 'class' => array( 'use-ajax pending_request_disapprove_link disapprove' . $vid ) ),
      )
  );
}

/**
 * Cancel request link
 */
function theme_sbq_user_relationships_pending_request_cancel_link($variables) {
  $uid = $variables['uid'];
  $rid = $variables['rid'];
  $vid = $variables['vid'];
  $ajax_token = 'pending_request_cancel' . $vid;
  return l(t('取消'), 'user/' . $uid . '/relationship/action/' . $rid . '/cancel', array(
      'query' => array( 'destination' => $ajax_token ),
      'attributes' => array( 'class' => 'use-ajax pending-cancel ' . $ajax_token )
      )
  );
}

/**
 * Link to user's profile
 */
function theme_sbq_user_relationships_user_link($variables) {
  $uid = $variables['uid'];
  return url("user/$uid", array( 'absolute' => TRUE ));
}

/**
 * add relationship link
 */
function theme_sbq_user_relationships_add_user_link($variables) {
  $uid = $variables['uid'];
  $rid = $variables['rid'];
  $vid = $variables['vid'];
  $relationships = user_relationships_load($vid);

  if ($rid == FRIEND_DOCTOR_PATIENT) {
    $replace = '+请求';
  } else {
    $replace = '+关注';
  }

  $ajax_token = 'user_relationships_' . $vid;
  return l($replace, "relationship/ajax/{$uid}/request/{$rid}/{$vid}?destination={$ajax_token}", array(
      'attributes' => array( 'class' => 'use-ajax ' . $ajax_token ) )
  );
}

/*
 * process message status
 */

function theme_sbq_user_relationships_process_status($variables) {
  $output = array(
      '#prefix' => '<div class="sbq-relationships-sent"><ul>',
      '#suffix' => '</ul></div>'
  );
  $li = '';
  foreach ($variables['relationships'] as $relationship) {
    $row = sbq_user_relationships_user_action($relationship, $variables['account']);
    if ($variables['type'] == 'sent') {
      $li .= "<li>请求<span name='name'>{$row['user']->name}</span>成为你的好友，<span class='cancel'>{$row[1]}</span></li>";
    } else {
      $li .= "<li><span name='name'>{$row['user']->name}</span>请求成为你的好友，<span class='cancel'>{$row[1]}</span></li>";
    }
  }
  if (empty($li)) {
    $li = "<li>暂无需要处理的请求</li>";
  }
  $output['#markup'] = $li;
  return render($output).theme('pager');
}

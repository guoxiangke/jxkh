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

  return l(t('取消关注'), "relationship/ajax/{$uid}/remove/{$rid}/$vid?destination=$ajax_token", array(
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
  $ajax_token = 'received' . $vid;
  return l(
      t('同意'), "user/{$uid}/relationship/action/{$rid}/approve", array(
      'query' => array( 'destination' => $ajax_token ),
      'attributes' => array( 'class' => array( 'use-ajax pending_request_approve_link '.$ajax_token ) ),
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
  $ajax_token = 'ignore' . $vid;
  return l(
      t('拒绝'), "user/{$uid}/relationship/action/{$rid}/disapprove", array(
      'query' => array( 'destination' => $ajax_token ),
      'attributes' => array( 'class' => array( 'use-ajax pending_request_disapprove_link refuse '.$ajax_token ) ),
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
  return l(t('取消请求'), 'user/' . $uid . '/relationship/action/' . $rid . '/cancel', array(
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
    $replace = '请求';
  } else {
    $replace = '关注';
  }
  $rand = uniqid();
  $ajax_token = 'user_relationships_' . $vid.$rand;
  return l($replace, "relationship/ajax/{$uid}/request/{$rid}/{$vid}?destination={$ajax_token}", array(
      'attributes' => array( 'class' => 'use-ajax sbq_add_follow_btn add ' . $ajax_token ) )
  );
}

/*
 * process message status
 * @see theme_sbq_user_relationships_pending_request_disapprove_link
 * @see theme_sbq_user_relationships_pending_request_approve_link
 */

function theme_sbq_user_relationships_process_status($variables) {
  global $user;
  $menu_sent_active = '';
  $menu_received_active = '';
  if ($variables['type'] == 'sent') {
    $menu_sent_active = 'class="active"';
  } elseif ($variables['type'] == 'received') {
    $menu_received_active = 'class="active"';
  }
  $nav = '<div class="sbq_nav">'
          .'<ul>'
            .'<li>'.l('系统消息', 'user/message').'</li>'
            .'<li '.$menu_sent_active.'>'.l('我发送的请求', 'user/'.$user->uid.'/relationship/default/sent').'</li>'
            .'<li '.$menu_received_active.'>'.l('我收到的请求', 'user/'.$user->uid.'/relationship/default/received').'</li>'
          .'</ul>'
        .'</div>';
  $output = array(
      '#prefix' => '<div class="sbq_user_message">'.$nav.'<div class="sbq_con"><ul>',
      '#suffix' => '</ul></div></div>'
  );
  $li = '';
  foreach ($variables['relationships'] as $relationship) {
    $row = sbq_user_relationships_user_action($relationship, $variables['account']);
    if ($variables['type'] == 'sent') {
      $li .= '<li><div class="sbq_text">请求'.$row['user']->name.'成为你的好友</div><div class="sbq_actions">'.$row[1].'</div></li>';
    } elseif ($variables['type'] == 'received') {
      $li .= '<li><div class="sbq_text">'.$row['user']->name.'</div>请求成为你的好友<div class="sbq_actions">'.$row[1].'</div></li>';
    }
  }
  if (empty($li)) {
    $li = "<li>暂无需要处理的请求</li>";
  }
  $output['#markup'] = $li;
  return render($output) . theme('pager');
}

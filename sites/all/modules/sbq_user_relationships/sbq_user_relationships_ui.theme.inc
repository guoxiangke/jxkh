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

  return l(t('移除'), "relationship/ajax/{$uid}/remove/{$rid}/$vid?destination=$ajax_token", array(
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
  return l(
      t('Approve'), "user/{$uid}/relationships/requested/{$rid}/approve", array(
      'title' => array( 'title' => t('Approve') ),
      'query' => drupal_get_destination(),
      'attributes' => array( 'class' => array( 'user_relationships_popup_link' ) ),
      )
  );
}

/**
 * Decline to pending relationship link
 */
function theme_sbq_user_relationships_pending_request_disapprove_link($variables) {
  $uid = $variables['uid'];
  $rid = $variables['rid'];
  return l(
      t('Decline'), "user/{$uid}/relationships/requested/{$rid}/disapprove", array(
      'title' => array( 'title' => t('Decline') ),
      'query' => drupal_get_destination(),
      'attributes' => array( 'class' => array( 'user_relationships_popup_link' ) ),
      )
  );
}

/**
 * Cancel request link
 */
function theme_sbq_user_relationships_pending_request_cancel_link($variables) {
  $uid = $variables['uid'];
  $rid = $variables['rid'];
  return l(
      t('Cancel'), "user/{$uid}/relationships/requested/{$rid}/cancel", array(
      'title' => array( 'title' => t('Cancel') ),
      'query' => drupal_get_destination(),
      'attributes' => array( 'class' => array( 'user_relationships_popup_link' ) ),
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
  $ajax_token = 'user_relationships_' . $vid;
  return l(t('关注'), "relationship/ajax/{$uid}/request/{$rid}/{$vid}?destination={$ajax_token}", array(
      'attributes' => array( 'class' => 'use-ajax ' . $ajax_token ) )
  );
}

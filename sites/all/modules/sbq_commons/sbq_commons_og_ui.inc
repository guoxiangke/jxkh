<?php

function sbq_og_ui_status_link($group_type, $gid, $field_name = NULL) {
    // Make sure Drupal Ajax framework javascript is around
    drupal_add_library('system', 'drupal.ajax');
    if (sbq_og_ui_subscribe($group_type, $gid, $field_name)) {
        $output = l(
                t('加入小组'), "group/{$group_type}/{$gid}/subscribe/ajax"
                , array(
            'attributes' => array('class' => 'use-ajax og_ui_status'),
                )
        );
        return $output;
    } elseif (sbq_og_ui_unsubscribe($group_type, $gid, $field_name)) {
        $output = l(
                t('退出小组'), "group/{$group_type}/{$gid}/unsubscribe/ajax", array(
            'attributes' => array('class' => 'use-ajax og_ui_status'),
                )
        );
        return $output;
    }

    return FALSE;
}

function sbq_og_ui_subscribe_ajax($group_type, $gid) {
    global $user;
    if (!$user->uid) {
        die('no login');
    }
    $account    = clone $user;
    $wrapper    = entity_metadata_wrapper($group_type, $gid);
    $entity     = entity_load_single($group_type, $gid);
    list($id, $vid, $bundle) = entity_extract_ids($group_type, $entity);
    $field_name = og_get_best_group_audience_field('user', $user->uid, $group_type, $bundle);

    // Indicate the OG membership state (active or pending).
    $state = og_user_access($group_type, $gid, 'subscribe without approval') ? OG_STATE_ACTIVE : OG_STATE_PENDING;

    if ($wrapper->access('view')) {
        $label = $wrapper->label();
    } else {
        $label = t('Private group');
        if ($state == OG_STATE_ACTIVE) {
            // Determine if a user can subscribe to a private group, when OG-access
            // module is enabled, and the group is set to private.
            $state = variable_get('og_ui_deny_subscribe_without_approval', TRUE) ? OG_STATE_PENDING : OG_STATE_ACTIVE;
        }
    }

    // Add group membership form.
    $og_membership = og_membership_create($group_type, $gid, 'user', $account->uid, $field_name, array('state' => $state));
    $og_membership->save();

    $commands[] = ajax_command_replace('.og_ui_status', sbq_og_ui_status_link($group_type, $gid));
    return array('#type' => 'ajax', '#commands' => $commands);
}

function sbq_og_ui_unsubscribe_ajax($group_type, $gid) {
    og_ungroup($group_type, $gid);
    og_invalidate_cache(array($gid));
    $commands[] = ajax_command_replace('.og_ui_status', sbq_og_ui_status_link($group_type, $gid));
    return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * @file
 * Page callbacks for Organic groups module.
 */

/**
 * Subscribe the current user to a group.
 *
 * @param $node
 *   The group node entity.
 * @param $uid
 *   Optional; The user ID of the subscribing user. If empty the current user
 *   will be used.
 */
function sbq_og_ui_subscribe($entity_type, $etid, $field_name = NULL) {
    global $user;
    $entity_info = entity_get_info($entity_type);
    if (!$entity_type || !$entity_info) {
        // Not a valid entity type.
        return;
    }
    $entity = entity_load_single($entity_type, $etid);
    if (!$entity || !og_is_group($entity_type, $entity)) {
        // Not a valid entity, or not a group.
        return;
    }

    list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);

    if (empty($field_name)) {
        $field_name = og_get_best_group_audience_field('user', $user->uid, $entity_type, $bundle);
        if (empty($field_name)) {
            // User entity has no group audience field.
            return;
        }
    }

    $field    = field_info_field($field_name);
    $instance = field_info_instance('user', $field_name, 'user');
    $account  = user_load($user->uid);

    if (empty($instance) || !field_access('view', $field, 'user', $account)) {
        // Field name given is incorrect, or user doesn't have access to the field.
        return;
    }

    if (!$user->uid) {
        // Anonymous user can't request membership.
        $dest = drupal_get_destination();
        if (variable_get('user_register', 1)) {
            drupal_set_message(t('In order to join any group, you must <a href="!login">login</a>. After you have successfully done so, you will need to request membership again.', array('!login' => url("user/login", array('query' => $dest)))));
        } else {
            drupal_set_message(t('In order to join any group, you must <a href="!login">login</a> or <a href="!register">register</a> a new account. After you have successfully done so, you will need to request membership again.', array('!register' => url("user/register", array('query' => $dest)), '!login' => url("user/login", array('query' => $dest)))));
        }
        return;
    }

    $redirect = FALSE;
    $message  = '';

    $params           = array();
    $params['@user']  = format_username($user);
    // Show the group name only if user has access to it.
    $params['@group'] = entity_access('view', $entity_type, $entity) ? entity_label($entity_type, $entity) : t('Private group');

    if (og_is_member($entity_type, $id, 'user', $user, array(OG_STATE_BLOCKED))) {
        // User is blocked, access denied.
        drupal_access_denied();
        return;
    }
    if (og_is_member($entity_type, $id, 'user', $user, array(OG_STATE_PENDING))) {
        // User is pending, return them back.
        $message  = $user->uid == $user->uid ? t('You already have a pending membership for the group @group.', $params) : t('@user already has a pending membership for the  the group @group.', $params);
        $redirect = TRUE;
    }

    if (og_is_member($entity_type, $id, 'user', $user, array(OG_STATE_ACTIVE))) {
        // User is already a member, return them back.
        $message  = $user->uid == $user->uid ? t('You are already a member of the group @group.', $params) : t('@user is already a member of the group @group.', $params);
        $redirect = TRUE;
    }

    if (!$message && $field['cardinality'] != FIELD_CARDINALITY_UNLIMITED) {
        // Check if user is already registered as active or pending in the maximum
        // allowed values.
        $wrapper = entity_metadata_wrapper('user', $account->uid);
        if ($field['cardinality'] == 1) {
            $count = $wrapper->{$field_name}->value() ? 1 : 0;
        } else {
            $count = $wrapper->{$field_name}->count();
        }
        if ($count >= $field['cardinality']) {
            $message  = t('You cannot register to this group, as you have reached your maximum allowed subscriptions.');
            $redirect = TRUE;
        }
    }

    if ($redirect) {
        // drupal_set_message($message, 'warning');
        // $url = entity_uri($entity_type, $entity);
        // drupal_goto($url['path'], $url['options']);
        return;
    }

    if (og_user_access($entity_type, $id, 'subscribe', $user) || og_user_access($entity_type, $id, 'subscribe without approval', $user)) {
        // Show the user a subscription confirmation.
        //return drupal_get_form('sbq_og_ui_confirm_subscribe', $entity_type, $id, $user, $field_name);
        return TRUE;
    }
}

/**
 * Confirm OG unsubscription form.
 *
 * The unsubscribing user is always the acting user - like this we make sure
 * no malicious user will unsubscribe another user. Administrators can reject or
 * ban another group member from the "people" page.
 */
function sbq_og_ui_unsubscribe($group_type, $gid) {
    global $user;
    $account = clone $user;
    $group   = entity_load_single($group_type, $gid);
    if (!$group || !og_is_group($group_type, $group)) {
        // Not a valid entity, or not a group.
        //   drupal_not_found();
        return;
    }

    // Check the user isn't the manager of the group.
    if ($group->uid != $user->uid) {
        if (og_is_member($group_type, $gid, 'user', $account, array(OG_STATE_ACTIVE, OG_STATE_PENDING))) {
            // Show the user a subscription confirmation.
            //return drupal_get_form('sbq_og_ui_confirm_unsubscribe', $group_type, $group);
            return TRUE;
        }
        //  drupal_access_denied();
        return;
    }
}

/**
 * 显示小组成员提升/移除管理员ajax连接
 * @param type $group_type node
 * @param type $gid node id
 * @param type $og_membership_id  userid 
 */
function sbq_group_upgrade_remove_member_status($group_type, $gid, $og_membership_id) {
    drupal_add_library('system', 'drupal.ajax');
    $group = entity_load_single($group_type, $gid);
    if(!$group || !og_is_group($group_type, $group)){
        return NULL;
    }
    if ($og_membership_id) {
        $account = user_load($og_membership_id);
    } else {
        global $user;
        $account = user_load($user->uid);
    }
    list(,, $bundle) = entity_extract_ids($group_type, $group);
    $og_roles      = og_roles($group_type, $bundle, $gid, FALSE, FALSE);
//    get null why？
//    $entities      = og_membership_load_multiple(array(), array('etid' => $account->uid, 'gid' => $gid, 'state' => 1));
//    $og_membership = reset($entities);
    $og_membership = og_get_membership($group_type, $gid, 'user', $account->uid);
    if(!$og_membership){
         if(!og_user_access($group_type, $gid, $og_membership->id)){
             return NULL;
         }
    }
    if ($og_roles) {
        $current_role = og_get_user_roles($group_type, $gid, $account->uid);
    }
    $link = '';
    foreach ($og_roles as $rid => $role) {
        if (isset($current_role[$rid])) {
            $href       = "group/{$group_type}/{$gid}/membership/action-role/{$og_membership->id}/{$rid}/0/ajax";
            $attributes = array(
                'attributes' => array('class' => array('use-ajax')),
            );
            $link .= l('移除', $href, $attributes) . $role;
        } else {
            $l = l('提升', "group/{$group_type}/{$gid}/membership/action-role/{$og_membership->id}/{$rid}/1/ajax", array(
                'attributes' => array('class' => array('use-ajax')),
                    )
            );
            $link .= $l . $role;
        }
    }

    return '<div id="og_action_role">' . $link . '</div>';
}

/**
 * 提升/移除小组成员角色
 * @param type $group_type
 * @param type $gid
 * @param type $og_membership
 * @param type $action_role
 * @param type $role_status
 */
function group_membership_action_role_ajax($group_type, $gid, $og_membership, $action_role, $role_status) {
    $roles = og_get_user_roles($group_type, $gid, $og_membership->etid);
    if ((int) $role_status === 0) {
        if (in_array($action_role, array_keys($roles))) {
            og_role_revoke($group_type, $gid, $og_membership->etid, $action_role);
        }
    } elseif ((int) $role_status === 1) {
        if (!in_array($action_role, array_keys($roles))) {
            og_role_grant($group_type, $gid, $og_membership->etid, $action_role);
        }
    }
    og_invalidate_cache(array($gid));
    $commands[] = ajax_command_replace('#og_action_role', sbq_group_upgrade_remove_member_status($group_type, $gid, $og_membership->etid));
    return array('#type' => 'ajax', '#commands' => $commands);
}

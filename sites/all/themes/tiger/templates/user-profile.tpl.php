<?php

/**
 * @file
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * Use render($user_profile) to print all profile items, or print a subset
 * such as render($user_profile['user_picture']). Always call
 * render($user_profile) at the end in order to print all remaining items. If
 * the item is a category, it will contain all its profile items. By default,
 * $user_profile['summary'] is provided, which contains data on the user's
 * history. Other data can be included by modules. $user_profile['user_picture']
 * is available for showing the account picture.
 *
 * Available variables:
 *   - $user_profile: An array of profile items. Use render() to print them.
 *   - Field variables: for each field instance attached to the user a
 *     corresponding variable is defined; e.g., $account->field_example has a
 *     variable $field_example defined. When needing to access a field's raw
 *     values, developers/themers are strongly encouraged to use these
 *     variables. Otherwise they will have to explicitly specify the desired
 *     field language, e.g. $account->field_example['en'], thus overriding any
 *     language negotiation rule that was previously applied.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 *
 * @ingroup themeable
 */
?>
<?php unset($user_profile['user_picture']); ?>
<?php unset($user_profile['user_badges']); ?>
<?php unset($user_profile['profile_main']); ?>
<?php unset($user_profile['og_user_node']); ?>
<?php unset($user_profile['summary']); ?>
<?php unset($user_profile['privatemsg_send_new_message']); ?>
<?php unset($user_profile['user_relationships_ui']); ?>
<?php unset($user_profile['userpoints']); ?>
<?php
  global $user;
  $uid = arg(1);
  $is_doctor = FALSE;
  if (in_array('doctor', $user->roles)) {
    $is_doctor = TRUE;
  }
?>
<div class="sbq_nav">
  <ul>
    <li class="active"><?php print l('资料', 'user/'.$uid); ?></li>
    <?php if ($user->uid == $uid):?>
    <li><?php print l('编辑账户资料', 'user/'.$uid.'/edit'); ?></li>
    <?php if ($is_doctor):?>
    <li><?php print l('编辑医生注册信息', 'user/'.$uid.'/edit/doctor_profile'); ?></li>
    <li><?php print l('编辑医生认证信息', 'user/'.$uid.'/edit/doctor_private_profile'); ?></li>
    <?php else:?>
    <li><?php print l('编辑患者公开信息', 'user/'.$uid.'/edit/customer_profile'); ?></li>
    <li><?php print l('编辑患者私人信息', 'user/'.$uid.'/edit/patient_private_profile'); ?></li>
    <?php endif;?>
    <?php endif;?>
  </ul>
</div>
<div class="sbq_user_date">
  <?php print render($user_profile); ?>
</div>

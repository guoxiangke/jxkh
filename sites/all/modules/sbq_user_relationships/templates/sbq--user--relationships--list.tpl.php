<?php
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 * $title
 * $account
 */
?>
<?php
  global $user;
  $uid = $user->uid;
  $menu_default_doctor = '';
  $menu_default_patient = '';
  $menu_recommand_doctor = '';
  $menu_recommand_patient = '';
  if (in_array('default', arg()) && in_array('doctor', arg())) {
    $menu_default_doctor = 'class="active"';
  } elseif (in_array('default', arg()) && in_array('patient', arg())) {
    $menu_default_patient = 'class="active"';
  } elseif (in_array('recommand', arg()) && in_array('doctor', arg())) {
    $menu_recommand_doctor = 'class="active"';
  } elseif (in_array('recommand', arg()) && in_array('patient', arg())) {
    $menu_recommand_patient = 'class="active"';
  } else {
    $menu_default_doctor = 'class="active"';
  }
?>
<div class="sbq_user_friends">
  <div class="sbq_nav">
    <ul>
      <li <?php print $menu_default_doctor; ?>><?php print l('医生圈', 'user/'.$uid.'/relationship/default/doctor'); ?></li>
      <li <?php print $menu_default_patient; ?>><?php print l('病友圈', 'user/'.$uid.'/relationship/default/patient'); ?></li>
      <li <?php print $menu_recommand_doctor; ?>><?php print l('推荐医生', 'user/relationship/recommand/doctor'); ?></li>
      <li <?php print $menu_recommand_patient; ?>><?php print l('推荐患者', 'user/relationship/recommand/patient'); ?></li>
    </ul>
  </div>
  <div class="sbq_con">
    <ul>
  <?php foreach ($accounts as $account) : ?>
    <?php
    print sbq_user_relationships_profile($account);
    ?>
  <?php endforeach; ?>
    </ul>
  </div>
  <?php if(!isset($accounts) || empty($accounts)):?>
  <span class="user-relationship-empty">暂无关系，请添加！</span>
  <?php endif;?>
</div>

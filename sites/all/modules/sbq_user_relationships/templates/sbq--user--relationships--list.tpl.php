<?php
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 * $title 
 * $account
 */
?>
<div class="sbq_user_relationships">
  <?php if (isset($title)): ?>
    <div class="relationship-title">
      <?php echo $title; ?>
    </div>
  <?php endif; ?>
  
  <?php foreach ($accounts as $account) : ?>
    <?php
    print sbq_user_relationships_profile($account);
    ?>
  <?php endforeach; ?>
  <?php if(!isset($accounts) || empty($accounts)):?>
  <span class="user-relationship-empty">暂无关系，请添加！</span>
  <?php endif;?>
</div>

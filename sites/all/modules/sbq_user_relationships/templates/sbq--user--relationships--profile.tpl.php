<?php
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
?>
<?php if ($view == 'list'): ?>
  <li>
    <div class="sbq_user_pic"><?php print $image; ?></div>
    <div class="sbq_content">
      <div class="sbq_user_name"><a href="/user/<?php print $profile['uid']; ?>"><?php print $profile['name']; ?></a></div>
      <div class="sbq_follow"><?php print $profile['follow']; ?></div>
    </div>
  </li>
<?php elseif ($view == 'block') : ?>
<li>
  <div class="sbq_user_pic"><?php print $image ?></div>
  <div class="sbq_content">
    <div class="sbq_user_name"><a href="/user/<?php print $profile['uid']; ?>"><?php print $profile['name']; ?></a></div>
    <?php if (isset($profile['bedges']) && strlen(trim($profile['bedges'])) > 0): ?>
    <div class="sbq_user_badge"><?php print $profile['bedges']; ?></div>
    <?php endif; ?>
    <div class="sbq_follow"><?php print $profile['follow']; ?></div>
    <div class="sbq_text"><a href="/user/<?php print $profile['uid']; ?>/qa/answer">回答了 <?php print $profile['answers_count']; ?> 个问题</a></div>
  </div>
</li>
<?php endif; ?>

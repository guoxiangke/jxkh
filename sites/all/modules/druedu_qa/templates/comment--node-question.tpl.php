<?php
hide($content['links']['#links']['comment-reply']);
hide($content['links']);
?>
<div class="comment clearfix">
  <? //php print $picture;  ?>
  <div class="submitted clearfix">
    <div class="comment_content pull-left span11">
      <span class="comment-text">
        <?php print render($content['comment_body']); ?> 
        –   
        <span class="user_info">
          <?php print $submitted; ?>
        </span>

        <?php
        global $user;
        if (($content['comment_body']['#object']->uid == $user->uid && user_access('edit comments')) || user_access('administer comments')):
          ?>
          <span class="actions">
            <?php print render($content['links']) ?>
          </span>
        <?php endif; ?>
      </span>
    </div>
    <div class="label-new pull-right span1">
      <?php if (FALSE): ?>
        <?php if ($new): ?>
          <span class="label label-success pull-right"><?php print $new; ?></span>
        <?php endif; ?>
      <?php endif; ?>
    </div>
  </div>

</div>

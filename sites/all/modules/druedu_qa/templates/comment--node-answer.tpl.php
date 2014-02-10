
<div class="sbq_user_pic">
  <div class="user-picture">
    <?php print $picture; ?>
  </div>
</div>
<div class="sbq_reply_list_content">
  <div class="sbq_user_name">
    <?php print $author; ?>
  </div>
  <div class="sbq_text">
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['links']);
      print render($content);
    ?>
  </div>
  <div class="sbq_date"><?php print $created; ?></div>
</div>

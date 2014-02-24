<?php
// Each file loads it's own styles because we cant predict which file will be
// loaded.
drupal_add_css(drupal_get_path('module', 'privatemsg') . '/styles/privatemsg-view.base.css');
drupal_add_css(drupal_get_path('module', 'privatemsg') . '/styles/privatemsg-view.theme.css');
$my = '';
if ($self) {
  $my = ' my';
}
?>
<?php print $anchors; ?>
<div class="sbq_pm_item<?php print $my; ?>">
  <div class="sbq_user_pic"><?php print $author_picture; ?></div>
  <div class="sbq_content">
    <div class="sbq_arrow"></div>
    <div class="sbq_head">
      <div class="sbq_user_name"><?php print $author_name_link; ?></div>
      <div class="sbq_date"><?php print $message_timestamp; ?></div>
    </div>
    <div class="sbq_text"><?php print $message_body; ?></div>
  </div>
</div>

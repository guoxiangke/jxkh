<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
$menu_advice_active = '';
$menu_report_active = '';
$menu_symptom_active = '';
$menu_diary_active = '';
$menu_other_active = '';

$url_query = drupal_get_query_parameters();
$url_records = $url_query['records'];
if ($url_records == '医嘱') {
  $menu_advice_active = ' class="active"';
} elseif ($url_records == '化验单') {
  $menu_report_active = ' class="active"';
} elseif ($url_records == '症状') {
  $menu_symptom_active = ' class="active"';
} elseif ($url_records == '生活日记') {
  $menu_diary_active = ' class="active"';
} elseif ($url_records == '其他') {
  $menu_other_active = ' class="active"';
}

?>
<div class="sbq_notes_list">
  <div class="sbq_nav">
    <ul>
      <li<?php print $menu_advice_active; ?>><?php print l('医嘱', 'user/records', array('query' => array('records' => '医嘱'))); ?></li>
      <li<?php print $menu_report_active; ?>><?php print l('化验单', 'user/records', array('query' => array('records' => '化验单'))); ?></li>
      <li<?php print $menu_symptom_active; ?>><?php print l('症状', 'user/records', array('query' => array('records' => '症状'))); ?></li>
      <li<?php print $menu_diary_active; ?>><?php print l('生活日记', 'user/records', array('query' => array('records' => '生活日记'))); ?></li>
      <li<?php print $menu_other_active; ?>><?php print l('其他', 'user/records', array('query' => array('records' => '其他'))); ?></li>
    </ul>
  </div>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($header): ?>
    <div class="view-header">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_before): ?>
    <div class="attachment attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <?php if ($rows): ?>
    <div class="sbq_con">
      <?php print $rows; ?>
    </div>
  <?php elseif ($empty): ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager): ?>
    <?php print $pager; ?>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>

</div><?php /* class view */ ?>

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
 // $main_title = drupal_get_title();
 // if($main_title=='QA') {//???
 //   $main_title = 'All Questions';
 // }
 // echo "<h1>$main_title</h1>";
?>
<?php
  // get tags
  if ($cache = cache_get('sbq_questions_list_tags')) {
    $tags_output = $cache->data;
  }
  else {
    // Create data.
    $vocabulary = taxonomy_vocabulary_machine_name_load('tags');
    $terms = taxonomy_get_tree($vocabulary->vid);
    $tags_output = '';
    foreach ($terms as $key => $tag) {
      $tag_title = trim($tag->name);
      $tid = trim($tag->tid);
      if (strlen($tag_title)>0 && $tid>0) {
        $tag_count = 0;
        $nids = taxonomy_select_nodes($tid, FALSE);
        foreach($nids as $nid) {
          $node = node_load($nid);
          if ($node->type == 'question' && $node->status) {
            $tag_count++;
          }
        }
        if ($tag_count > 5) {
          $tags_output .= '<li>'
            . '<a href="'.url('questions/tagged/').'?field_tags_tid='.$tag_title.'">'
            . '<span class="sbq_tit">'.$tag_title.'</span>'
            . '<span class="sbq_num">'.$tag_count.'</span>'
            . '</a>';
        }
      }
    }
    cache_set('sbq_questions_list_tags', $tags_output);
  }
?>
<div class="sbq_question_list">
  <div class="sbq_tags">
    <ul>
      <?php print $tags_output; ?>
    </ul>
  </div>
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h2 class="sbq_list_title"><?php print $title; ?></h2>
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
    <div class="sbq_question_list_inner view-content">
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

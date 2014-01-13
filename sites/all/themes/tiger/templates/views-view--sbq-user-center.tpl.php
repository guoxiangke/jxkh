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
?>
<div class="sbq_user_article_list">
  <?php
    global $user;
    if (is_numeric(arg(1)) && arg(1)!=$user->uid) {
      $account = user_load(arg(1));
    } else {
      $account = $user;
    }

    $blog_active = FALSE;
    if (in_array('blog', arg())) {
      $blog_active = TRUE;
      $menu_promoted_active = '';
      $menu_blog_active = '';
      if (in_array('promoted', arg())) {
        $menu_promoted_active = 'class="active"';
      } else {
        $menu_blog_active = 'class="active"';
      }
    }

    $qa_active = FALSE;
    if (in_array('qa', arg())) {
      $qa_active = TRUE;
      $menu_promoted_active = '';
      $menu_followed_active = '';
      $menu_ask_active = '';
      $menu_answer_active = '';
      if (in_array('promoted', arg())) {
        $menu_promoted_active = 'class="active"';
      } elseif (in_array('followed', arg())) {
        $menu_followed_active = 'class="active"';
      } elseif (in_array('ask', arg())) {
        $menu_ask_active = 'class="active"';
      } elseif (in_array('answer', arg())) {
        $menu_answer_active = 'class="active"';
      }
    }

  ?>

  <div class="sbq_nav">
    <ul>
      <?php if ($blog_active): ?>
        <?php if ($account->uid==$user->uid): ?>
          <li <?php print $menu_promoted_active; ?>><?php print l('推荐文章', 'user/blog/promoted'); ?></li>
        <?php endif; ?>
          <li <?php print $menu_blog_active; ?>><?php print l('我的文章', 'user/'.$account->uid.'/blog'); ?></li>
      <?php endif; ?>
      <?php if ($qa_active): ?>
        <?php if ($account->uid==$user->uid): ?>
          <li <?php print $menu_promoted_active; ?>><?php print l('推荐问答', 'user/qa/promoted'); ?></li>
          <li <?php print $menu_followed_active; ?>><?php print l('我关注的问答', 'user/qa/followed'); ?></li>
        <?php endif; ?>
          <li <?php print $menu_ask_active; ?>><?php print l('我的提问', 'user/'.$account->uid.'/qa/ask'); ?></li>
          <li <?php print $menu_answer_active; ?>><?php print l('我的回答', 'user/'.$account->uid.'/qa/answer'); ?></li>
      <?php endif; ?>
    </ul>
    <?php if ($blog_active): ?>
      <?php if ($account->uid==$user->uid): ?>
        <?php print l('发布文章', 'node/add/blog', array('attributes' => array('class' => 'sbq_add_btn'))); ?>
      <?php endif; ?>
    <?php endif; ?>
    <?php if ($qa_active): ?>
      <?php if ($account->uid==$user->uid): ?>
        <?php print l('发布问题', 'node/add/question', array('attributes' => array('class' => 'sbq_add_btn'))); ?>
      <?php endif; ?>
    <?php endif; ?>
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

  <?php if ($exposed): ?>
    <div class="view-filters">
      <?php print $exposed; ?>
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

<?php

/**
 * @file
 * Default theme implementation to provide an HTML container for comments.
 *
 * Available variables:
 * - $content: The array of content-related elements for the node. Use
 *   render($content) to print them all, or
 *   print a subset such as render($content['comment_form']).
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default value has the following:
 *   - comment-wrapper: The current template type, i.e., "theming hook".
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * The following variables are provided for contextual information.
 * - $node: Node object the comments are attached to.
 * The constants below the variables show the possible values and should be
 * used for comparison.
 * - $display_mode
 *   - COMMENT_MODE_FLAT
 *   - COMMENT_MODE_THREADED
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess_comment_wrapper()
 *
 * @ingroup themeable
 */
?>
<?php
  global $user;
  $name = theme('username', array('account' => $user));
  $picture = theme('user_picture', array('account' =>$user));
?>
<div id="comments" class="sbq_comment">
  <?php if ($content['comments'] && $node->type != 'forum'): ?>
    <div class="sbq_comment_head">
      <div class="sbq_title">最新评论</div>
    </div>
  <?php endif; ?>
  <div class="sbq_comment_list">
  <?php print render($content['comments']); ?>
  </div>
  <?php if ($content['comment_form']): ?>
    <div class="sbq_reply_info">
      <div class="sbq_user_name"><?php print $name; ?></div>
      <div class="sbq_user_pic"><?php print $picture; ?></div>
    </div>
    <div class="comment_textarea_02">
    <?php print render($content['comment_form']); ?>
    </div>
  <?php endif; ?>
</div>

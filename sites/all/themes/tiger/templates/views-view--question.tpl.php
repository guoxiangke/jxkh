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
/**
 * Crystal Q&A comments system vars
 * @see crystal_qa_preprocess_views_view()
 */
?>
<div class="sbq_question_final">
  <?php if ($rows): ?>
    <?php print $rows; ?>
  <?php elseif ($empty): ?>
    <div class="view-empty">
        <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div id = "answers" class="attachment attachment-after">
      <div id="new_answer">
      </div>
    </div>
    <?php print $attachment_after; ?>
    <?php
      $answers_count = 0;
      if (arg(0) == 'question' && is_numeric(arg(1)) && ! arg(2)) {
        $node = node_load(arg(1));
        $answers_count = $node->field_computed_answers['und'][0]['value'];
      }
      // TODO : Load More answers by ajax
      // Answers are views attachment
    ?>
    <?php if ($answers_count > 50): ?>
      <a class="sbq_more_link">更多</a>
    <?php endif; ?>
  <?php endif; ?>
  <?php if (isset($answer_node_form)): ?>
    <?php
      global $user;
      if ($user->uid > 0) {
        $a_name = theme('username', array('account' => $user));
        $a_picture = theme('user_picture', array('account' =>$user));
        ?>
        <div class="sbq_answer_info">
          <div class="sbq_user_name"><?php print $a_name; ?></div>
          <div class="sbq_user_pic"><?php print $a_picture; ?></div>
        </div>
        <div class="sbq_answer_form">
          <div class="answer-node-form">
            <?php print render($answer_node_form); // render answer_node_form for question  ?>
          </div>
        </div>
        <?php
      } else {
        # code...
      }
    ?>
  <?php endif; ?>
</div><?php /* class view */ ?>

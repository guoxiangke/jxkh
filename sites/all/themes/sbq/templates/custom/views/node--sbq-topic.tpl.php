<?php

/**
 * @file
 * Bartik's theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
?>
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
<div class="sbq_topic_title sbq_topic_title_rap"> 
  <h1 class="page-header"><?php echo $node->title;?></h1> 
</div>
<div class="sbq_topic_comments">
  全部讨论:
  <span class="counts">
  <?php echo $node->comment_count;?>
  </span>
</div>
  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h2<?php print $title_attributes; ?>>
      <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
    </h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($display_submitted): ?>
    <div class="meta submitted">
      <?php print $user_picture; ?>
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>

  <div class="content clearfix" <?php print $content_attributes; ?> >
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
       // Append comment form if needed.
     if (user_access('post comments')) {
        $build = drupal_get_form("comment_node_{$node->type}_form", (object) array('nid' => $node->nid));
        $additions['comment_form'] = $build;
      }

      if (isset($additions)) {
        $additions += array(
          '#theme' => 'comment_wrapper__node_' . $node->type,
          '#node' => $node,
          'comments' => array(),
          'comment_form' => array(),
        );
      }  
      //rate_get_results('node', $nid, $widget_id);
      // dpm(rate_get_results('node', $node->nid, 1));
      $rete_result = rate_get_results('node', $node->nid, 1);
      if(user_is_logged_in()) {
        print render($additions['comment_form']);
      }else {
        print '<form class="comment-form" action="/comment/reply/" method="post" id="comment-form--2" accept-charset="UTF-8"><div><div class="field-type-text-long field-name-comment-body field-widget-text-textarea form-wrapper" id="edit-comment-body--2"><div id="comment-body-add-more-wrapper--2"><div class="text-format-wrapper"><div class="control-group form-type-textarea form-item-comment-body-und-0-value form-item">
  
<div class="controls"> <div class="form-textarea-wrapper resizable textarea-processed resizable-textarea"><textarea class="text-full ckeditor-mod form-textarea required" id="edit-comment-body-und-0-value--2" name="comment_body[und][0][value]" cols="60" rows="5" disabled="disabled">您还没有登录，请登录后发布观点：禁止发布含有XXX的词汇</textarea><div class="grippie"></div></div>
</div></div>

</div>
</div></div>


<button class="btn form-submit ajax-processed" id="edit-submit--3" name="op" value="发表观点" type="submit" disabled="disabled">发表观点</button>
</div></form>';
      }
   ?>
  </div>

  <?php
    // Remove the "Add new comment" link on the teaser page or if the comment
    // form is being displayed on the same page.
    if ($teaser || !empty($content['comments']['comment_form'])) {
      unset($content['links']['comment']['#links']['comment-add']);
    }
    // Only display the wrapper div if there are links.
    $links = render($content['links']);
    if ($links):
  ?>
    <div class="link-wrapper">
      <?php print $links; ?>
    </div>
  <?php endif; ?>

  <?php
  // print render($content['comments']); 
  ?>

</div>



<div class="sbq_topic_statics">

</div>
<div class="sbq-center-box">
  <div class="sbq_topic_comments_approve">
    <div class="sbq_topic_comments_head">支持的观点</div>
    <?php 
    // $view = views_get_view('show_sbq_topic_comments');
    // $view->init();
    // $view->set_display('page_approve');
    // $view->execute();
    // print $view->render();  

    print views_embed_view('show_sbq_topic_comments',"page_approve");

    //  $view = views_get_view('show_sbq_topic_comments');
    //  // $handler = $view->new_display('block', 'Block', 'block_reply');
    //  // $handler->display->display_options['filters']['combine']['value'] = '0';
    // $view->set_display('block_reply');
    // $view->display['block_reply']->handler->display->display_options['filters']['combine']['value'] = '8';
    // dpm($view->display['block_reply']->handler->display->display_options);
    // print $view->preview();
    // print views_embed_view('show_sbq_topic_comments',"block_reply");

    // $view->display['block_reply']->handler->options['title'] = $title;

         //replace $user->uid with value you wish to sort by: ie, 'ag'
    // $output = views_build_view('page_reply', $view, null, false, 0, 0, 0, array(0 => array('op' => '=', 'filter' => $user->uid)));
//div bug!
    //@see sbq_topic_views_comment_print

    ?>
  </div>
  </div>
  <div class="sbq_topic_comments_reject">
    <div class="sbq_topic_comments_head">反对的观点</div>
  <?php
    print views_embed_view('show_sbq_topic_comments',"page_reject");
  ?>
  </div>
</div>
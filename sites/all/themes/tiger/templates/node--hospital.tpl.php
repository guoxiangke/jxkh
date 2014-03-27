<?php

/**
 * @file
 * Default theme implementation to display a node.
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
 *
 * @ingroup themeable
 */

$image_path = file_create_url($node->field_image['und'][0]['uri']);
$edit_path = '/node/' . $node->nid . '/edit';
?>


<div class="sbq_ranking_hospital_final">
  <div class="sbq_title"><?php print $title; ?></div>
  <div class="sbq_info">
    
    <?php if ($image_path):?>
    <div class="sbq_img">
      <img src="<?php print $image_path; ?>"  alt="" width="240" height="160" border="0"/>
    </div>
    <?php endif;?>
    <div class="sbq_summary">
      <ul>
        <?php if (isset($content['field_alias_name'])):?>
        <li><span>医院别名：</span><?php print $content['field_alias_name']['#items'][0]['safe_value']; ?></li>
        <?php endif;?>
        <?php if (isset($content['field_hospital_nature'])):?>
        <li><span>医院性质：</span><?php print $content['field_hospital_nature'][0]['#markup']; ?></li>
        <?php endif;?>
        <?php if (isset($content['field_hospital_level'])):?>
        <li><span>医院等级：</span><?php print $content['field_hospital_level'][0]['#markup']; ?></li>
        <?php endif;?>
        <?php if (isset($content['field_hospital_phone'])):?>
        <li><span>联系电话：</span><?php print $content['field_hospital_phone']['#items'][0]['safe_value']; ?></li>
        <?php endif;?>
        <?php if (isset($content['field_hospital_website'])):?>
        <li><span>医院网址：</span><?php print $content['field_hospital_website']['#items'][0]['safe_value']; ?></li>
        <?php endif;?>
      </ul>
      <div class="sbq_score">
        <span>好评指数</span>
        <b><?php print render($content['field_rank_result']); ?></b>
        <a href="#">查看评价</a>
      </div>
    </div>
  </div>
  <div class="sbq_wrap sbq_details">
    <div class="sbq_head">
      <div class="sbq_title">医院详情</div>
    </div>
    <div class="sbq_content">
      <dl>
        <dt>医院名称：</dt>
        <dd><?php print $title; ?></dd>
      </dl>
      <?php if (isset($content['field_alias_name'])):?>
      <dl>
        <dt>医院别名：</dt>
        <dd><?php print render($content['field_alias_name']); ?></dd>
      </dl>
      <?php endif;?>
      <?php if (isset($content['field_hospital_nature'])):?>
      <dl>
        <dt>医院性质：</dt>
        <dd><?php print render($content['field_hospital_nature']); ?></dd>
      </dl>
      <?php endif;?>
      <?php if (isset($content['field_hospital_level'])):?>
      <dl>
        <dt>医院等级：</dt>
        <dd><?php print render($content['field_hospital_level']); ?></dd>
      </dl>
      <?php endif;?>
      <?php if (isset($content['field_hospital_phone'])):?>
      <dl>
        <dt>联系电话：</dt>
        <dd><?php print render($content['field_hospital_phone']); ?></dd>
      </dl>
      <?php endif;?>
      <?php if (isset($content['field_hospital_beds'])):?>
      <dl>
        <dt>住院床位：</dt>
        <dd><?php print render($content['field_hospital_beds']); ?></dd>
      </dl>
      <?php endif;?>
      <?php if (isset($content['field_hospital_doctors'])):?>
      <dl>
        <dt>医生人数：</dt>
        <dd><?php print render($content['field_hospital_doctors']); ?></dd>
      </dl>
      <?php endif;?>
      <?php if (isset($content['field_outpatients'])):?>
      <dl>
        <dt>年门诊量：</dt>
        <dd><?php print render($content['field_outpatients']); ?></dd>
      </dl>
      <?php endif;?>
      <?php if (isset($content['field_hospital_care'])):?>
      <dl>
        <dt>是否医保：</dt>
        <dd><?php print render($content['field_hospital_care']); ?></dd>
      </dl>
      <?php endif;?>
      <?php if (isset($content['field_hospital_website'])):?>
      <dl>
        <dt>医院网址：</dt>
        <dd><?php print render($content['field_hospital_website']); ?></dd>
      </dl>
      <?php endif;?>
      <?php if (isset($content['field_hospital_address'])):?>
      <dl>
        <dt>联系地址：</dt>
        <dd><?php print render($content['field_hospital_address']); ?></dd>
      </dl>
      <?php endif;?>
      <?php if (isset($content['field_departments'])):?>
      <dl class="all">
        <dt>特色科室：</dt>
        <dd><?php print render($content['field_departments']); ?></dd>
      </dl>
      <?php endif;?>
    </div>
  </div>
  <div class="sbq_wrap sbq_text">
    <div class="sbq_head">
      <div class="sbq_title">医院介绍</div>
      <div class="sbq_edit"><a href="<?php print $edit_path; ?>">编辑</a></div>
    </div>
    <div class="sbq_content">
      <?php
        // We hide the comments and links now so that we can render them later.
        hide($content['comments']);
        hide($content['links']);
        print render($content);
      ?>
    </div>
  </div>
</div>
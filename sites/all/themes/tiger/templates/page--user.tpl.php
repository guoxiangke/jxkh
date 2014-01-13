<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
<div class="header">
  <div class="header_inner">
    <?php if ($logo): ?>
    <div class="sbq_logo">
      <div class="sbq_img">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a>
      </div>
    </div>
    <?php endif; ?>
    <div class="sbq_main_nav">
      <?php if ($main_menu || $secondary_menu): ?>
        <?php print theme('links__system_main_menu', array('links' => $main_menu, 'attributes' => array('id' => 'main-menu', 'class' => array('links', 'inline', 'clearfix')))); ?>
      <?php endif; ?>
    </div>
    <div class="sbq_header_login">
      <?php if (!$logged_in): ?>
      <div class="sbq_user_links">
        <a href="/user/login" class="log">登录</a>|<a href="/customer/register">注册</a>
      </div>
      <div class="sbq_user_pic">
        <a href="#"><img src="../image/default_avatar.png" width="50" height="50"  alt=""/></a>
      </div>
      <?php endif; ?>
      <?php if ($logged_in): ?>
      <?php
        $name = theme('username', array('account' => $user));
        $picture = theme('user_picture', array('account' =>$user));
      ?>
      <div class="sbq_user_links">
        欢迎您，<?php print $name; ?>|<a href="/user/logout">退出</a>
      </div>
      <div class="sbq_user_pic">
        <?php print $picture; ?>
      </div>
      <?php endif; ?>
    </div>
  </div>
</div>
<?php if ($logged_in): ?>
<?php
  $a_name = theme('username', array('account' => $account));
  $a_picture = theme('user_picture', array('account' =>$account));
  $a_uid = $account->uid;

  $menu_blog_active = '';
  if (in_array('blog', arg())) {
    $menu_blog_active = 'class="active"';
  } elseif (isset($node) && $node->type == 'blog') {
    $menu_blog_active = 'class="active"';
  }
  $menu_qa_active = '';
  if (in_array('qa', arg())) {
    $menu_qa_active = 'class="active"';
  }
?>
<?php endif; ?>
<div class="body">
  <div class="main">
    <?php if ($logged_in): ?>
    <div class="sbq_user_headr"><img src="/sites/all/themes/tiger/image/sbq_user_headr_bg.jpg" width="960" height="200"  alt=""/></div>
    <div class="sbq_user_info">
      <div class="sbq_user_pic"><?php print $a_picture; ?></div>
      <div class="sbq_user_summary">
        <div class="sbq_user_name">
          <strong><?php print $a_name; ?></strong>
          <?php if (isset($field_doctor_title)): ?>
          <span><?php print $field_doctor_title; ?></span>
          <?php endif; ?>
          <?php if (isset($follow_link[0]) && isset($follow_link[0]['relationship_action'])): ?>
          <div class="sbq_user_follow">
            <?php print $follow_link[0]['relationship_action']; ?>
          </div>
          <?php endif; ?>
        </div>
        <?php if (isset($hospitals_departments)): ?>
        <div class="sbq_user_hospital"><?php print $hospitals_departments; ?></div>
        <?php elseif(isset($is_doctor) && $is_doctor): ?>
        <div class="sbq_user_hospital"><a href="/user/edit">填写所在医院及科室</a></div>
        <?php endif; ?>
      </div>
      <div class="sbq_user_follower">
        <ul>
          <?php if (isset($counts['user_relationship_count']['doctor_count'])): ?>
          <li><strong><?php print $counts['user_relationship_count']['doctor_count']; ?></strong><span>医生圈</span></li>
          <?php endif; ?>
          <?php if (isset($counts['user_relationship_count']['patient_count'])): ?>
          <li><strong><?php print $counts['user_relationship_count']['patient_count']; ?></strong><span>病友圈</span></li>
          <?php endif; ?>
          <?php if ($counts['user_question_count']>=0 && $counts['user_answer_count']>=0): ?>
          <li><strong><?php print $counts['user_question_count']; ?>/<?php print $counts['user_answer_count']; ?></strong><span>提问/回答</span></li>
          <?php endif; ?>
        </ul>
      </div>
    </div>

    <div class="sbq_user_menu">
      <ul>
        <li><a href="user_center.html">动态</a></li>
        <li <?php print $menu_blog_active; ?>><?php print l('文章', 'user/'.$a_uid.'/blog'); ?></li>
        <li <?php print $menu_qa_active; ?>><?php print l('问答', 'user/'.$a_uid.'/qa/ask'); ?></li>
        <li><a href="user_friends.html">圈子</a></li>
        <li><a href="user_message.html">消息</a></li>
        <li><a href="#">积分</a></li>
      </ul>
    </div>
    <?php endif; ?>
    <?php if ($page['sidebar_first']): ?>
      <div class="sidebar_first sidebar">
        <?php print render($page['sidebar_first']); ?>
      </div> <!-- /.sidebar-first -->
    <?php endif; ?>

    <div class="content">
      <?php print render($page['content']); ?>
    </div>

    <?php if ($page['sidebar_second']): ?>
      <div class="sidebar_second sidebar">
        <?php print render($page['sidebar_second']); ?>
      </div> <!-- /.sidebar-second -->
    <?php endif; ?>
  </div>
</div>
<div class="footer">
  <?php print render($page['footer']); ?>
</div> <!-- /#footer -->

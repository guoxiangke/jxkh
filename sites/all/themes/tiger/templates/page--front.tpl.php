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
          <img src="<?php print $logo; ?>" width="290" height="60" alt="<?php print t('Home'); ?>" />
        </a>
      </div>
    </div>
    <?php endif; ?>
    <div class="sbq_header_login">
      <div class="sbq_user_links"><a href="#">登录</a>|<a href="#">注册</a></div>
      <div class="sbq_user_pic"><a href="#"><img src="image/default_avatar.png" width="50" height="50"  alt=""/></a></div>
    </div>
  </div>
</div>
<div class="sbq_qr_code">
  <div class="sbq_qr_code_inner">
    <a href="#"><img src="images/qr_code.png" width="100" height="140"  alt=""/></a>
  </div>
</div>
<div class="body">
  <div class="main">
    <div class="sbq_home_menu">
      <ul class="sbq_patient">
        <?php print render($page['front_left']); ?>
      </ul>
      <ul class="sbq_doctor">
        <li class="color_04"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_02.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">圈子</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <?php print render($page['front_middle']); ?>
      </ul>
      <ul class="sbq_focus">
        <li class="color_03 pic"><a href="#">
          <div class="sbq_img"><img src="images/307.png" width="250" height="120"  alt=""/></div>
          <div class="sbq_title">307医院免疫学实验室</div>
          </a></li>
        <?php print render($page['front_right']); ?>
      </ul>
    </div>
  </div>
</div>
<div id="footer" class="footer">
  <?php print render($page['footer']); ?>
</div> <!-- /#footer -->

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
  $theme_path = drupal_get_path('theme', 'tiger');
  $node = node_load(2883);
  $sbq_activity_bg_uri = $node->field_image[LANGUAGE_NONE][0]['uri'];
  drupal_add_css(path_to_theme() . "/css/news.css", array('group' => CSS_THEME));
  drupal_add_css(path_to_theme() . "/css/form.css", array('group' => CSS_THEME));
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
        <a href="/user/login"><img src="/<?php print $theme_path; ?>/image/default_avatar.png" width="50" height="50"  alt=""/></a>
      </div>
      <?php endif; ?>
      <?php if ($logged_in): ?>
      <?php
        global $user;
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
<div class="sbq_activity_bg" style="background:url('<?php echo file_create_url($sbq_activity_bg_uri);?>')"></div>
<div class="body">
  <div class="main">
    <?php if ($messages): ?>
    <div class="sbq_messages">
      <?php print $messages; ?>
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

      <div class="sidebar_second sidebar">
        <div class="sbq_event_btn">
        <?php if ($logged_in):?>
          <a href="/node/2883">活动介绍</a>
        <?php else: ?>
          <a href="/user/login?destination=node/2883">立即参加</a>
        <?php endif; ?>
        </div>
        <?php
        // <div class="sbq_winner_list">
        //   <div class="sbq_head"><span class="sbq_title">获奖名单</span></div>
        //   <ul>
        //     <li><a href="#">张小平</a><span>iPad mini 2</span></li>
        //     <li><a href="#">Administrator</a><span>华为3c</span></li>
        //     <li><a href="#">adf569</a><span>荣耀3</span></li>
        //     <li><a href="#">adlw</a><span>50元充值卡</span></li>
        //     <li><a href="#">12223</a><span>50元充值卡</span></li>
        //     <li><a href="#">12223</a><span>50元充值卡</span></li>
        //     <li><a href="#">12223</a><span>50元充值卡</span></li>
        //     <li><a href="#">12223</a><span>50元充值卡</span></li>
        //     <li><a href="#">12223</a><span>50元充值卡</span></li>
        //     <li><a href="#">12223</a><span>50元充值卡</span></li>
        //   </ul>
        // </div>
        ?>
      </div> <!-- /.sidebar-second -->
  </div>
</div>
<div class="footer">
  <div class="footer_inner">
  <div class="sbq_about_link">
    <ul>
      <li><?php echo l('联系我们','node/2790');?></li>
      <li><?php echo l('注册服务条款','node/2789');?></li>
      <li><?php echo l('免责声明','node/2788');?></li>
      <li><?php echo l('加入我们','node/2787');?></li>
      <li><?php echo l('关于我们','node/2786');?></li>
    </ul>
  </div>
  <div class="sbq_copy">© 2014 伤不起 中国最真实的医疗评价平台(<a href="http://www.miitbeian.gov.cn" target="_bank"> 京ICP备13032461号-1</a>) </div>
  </div>
  <?php print render($page['footer']); ?>
</div> <!-- /#footer -->

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

  <div id="page-wrapper"><div id="page">

    <div id="header"><div class="section clearfix">

      <?php if ($logo): ?>
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a>
      <?php endif; ?>

      <?php if ($site_name || $site_slogan): ?>
        <div id="name-and-slogan">
          <?php if ($site_name): ?>
            <?php if ($title): ?>
              <div id="site-name"><strong>
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
              </strong></div>
            <?php else: /* Use h1 when the content title is empty */ ?>
              <h1 id="site-name">
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
              </h1>
            <?php endif; ?>
          <?php endif; ?>

          <?php if ($site_slogan): ?>
            <div id="site-slogan"><?php print $site_slogan; ?></div>
          <?php endif; ?>
        </div> <!-- /#name-and-slogan -->
      <?php endif; ?>

      <?php print render($page['header']); ?>

    </div></div> <!-- /.section, /#header -->

    <?php if ($main_menu || $secondary_menu): ?>
      <div id="navigation"><div class="section">
        <?php print theme('links__system_main_menu', array('links' => $main_menu, 'attributes' => array('id' => 'main-menu', 'class' => array('links', 'inline', 'clearfix')), 'heading' => t('Main menu'))); ?>
        <?php print theme('links__system_secondary_menu', array('links' => $secondary_menu, 'attributes' => array('id' => 'secondary-menu', 'class' => array('links', 'inline', 'clearfix')), 'heading' => t('Secondary menu'))); ?>
      </div></div> <!-- /.section, /#navigation -->
    <?php endif; ?>

    <?php if ($breadcrumb): ?>
      <div id="breadcrumb"><?php print $breadcrumb; ?></div>
    <?php endif; ?>

    <?php print $messages; ?>

    <div id="main-wrapper"><div id="main" class="clearfix">

      <div id="content" class="column"><div class="section">
        <?php if ($page['highlighted']): ?><div id="highlighted"><?php print render($page['highlighted']); ?></div><?php endif; ?>
        <a id="main-content"></a>
        <?php print render($title_prefix); ?>
        <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
        <?php print render($title_suffix); ?>
        <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
        <?php print render($page['help']); ?>
        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
        <?php print render($page['content']); ?>
        <?php print $feed_icons; ?>
      </div></div> <!-- /.section, /#content -->

      <?php if ($page['sidebar_first']): ?>
        <div id="sidebar-first" class="column sidebar"><div class="section">
          <?php print render($page['sidebar_first']); ?>
        </div></div> <!-- /.section, /#sidebar-first -->
      <?php endif; ?>

      <?php if ($page['sidebar_second']): ?>
        <div id="sidebar-second" class="column sidebar"><div class="section">
          <?php print render($page['sidebar_second']); ?>
        </div></div> <!-- /.section, /#sidebar-second -->
      <?php endif; ?>

    </div></div> <!-- /#main, /#main-wrapper -->

    <div id="footer"><div class="section">
      <?php print render($page['footer']); ?>
    </div></div> <!-- /.section, /#footer -->

  </div></div> <!-- /#page, /#page-wrapper -->
<!---------------------------------------------------------------------------->
<div class="header">
  <div class="header_inner">
    <div class="sbq_logo">
      <div class="sbq_img"><a href="#"><img src="image/logo.png" width="290" height="60"  alt=""/></a></div>
    </div>
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
        <li class="color_01"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_03.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">小组</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_02"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_12.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">问答</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_03"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_06.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">评测</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_05"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_07.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">活动</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_06"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_05.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">红黑榜</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_07 half"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_11.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">新闻</div>
          </a></li>
        <li class="color_07 half"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_10.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">曝光台</div>
          </a></li>
        <li class="color_07 half"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_08.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">爱心活动</div>
          </a></li>
        <li class="color_07 half"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_09.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">医界传奇 </div>
          </a></li>
        <li class="color_09"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_13.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">测试</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_10"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_13.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">测试</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_11"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_13.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">测试</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_12"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_13.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">测试</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_13"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_13.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">测试</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
      </ul>
      <ul class="sbq_doctor">
        <li class="color_04"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_02.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">圈子</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_08"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_04.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">医生馆</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_14"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_13.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">测试</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_15"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_13.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">测试</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_16"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_13.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">测试</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_17"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_13.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">测试</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
      </ul>
      <ul class="sbq_focus">
        <li class="color_03 pic"><a href="#">
          <div class="sbq_img"><img src="images/307.png" width="250" height="120"  alt=""/></div>
          <div class="sbq_title">307医院免疫学实验室</div>
          </a></li>
        <li class="color_03 pic"><a href="#">
          <div class="sbq_img"><img src="images/307.png" width="250" height="120"  alt=""/></div>
          <div class="sbq_title">12345678901234567890123456789012345678901234567890</div>
          </a></li>
        <li class="color_03 pic"><a href="#">
          <div class="sbq_img"><img src="images/307.png" width="250" height="120"  alt=""/></div>
          <div class="sbq_title">307医院免疫学实验室</div>
          </a></li>
        <li class="color_03 pic"><a href="#">
          <div class="sbq_img"><img src="images/307.png" width="250" height="120"  alt=""/></div>
          <div class="sbq_title">307医院免疫学实验室</div>
          </a></li>
        <li class="color_04"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_02.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">XX诊所</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
        <li class="color_18"><a href="#">
          <div class="sbq_img"><img src="images/sbq_home_icon_02.png" width="40" height="40"  alt=""/></div>
          <div class="sbq_title">XX诊所</div>
          <div class="sbq_text">小组相关介绍文字关介绍文字</div>
          </a></li>
      </ul>
    </div>
  </div>
</div>
<div class="footer">
  <div class="footer_inner">
    <div class="sbq_about_link">
      <ul>
        <li><a href="/node/2790">联系我们</a></li>
        <li><a href="/node/20151">注册服务条款</a></li>
        <li><a href="/node/2788">免责声明</a></li>
        <li><a href="/node/2787">加入我们</a></li>
        <li><a href="/node/2786">关于我们</a></li>
      </ul>
    </div>
    <div class="sbq_copy">Copyright&copy;<a href="http://www.miitbeian.gov.cn/state/outPortal/loginPortal.action" target="_bank">伤不起</a> ( 京ICP备13032461号-1 ) <a class="footer-logo" href="www.shangbq.com">中国最真实的医疗评价平台</a></div>
  </div>
</div>

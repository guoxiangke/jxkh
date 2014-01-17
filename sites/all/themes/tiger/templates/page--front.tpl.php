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
?>
<div class="header">
  <div class="header_inner">
    <?php if ($logo): ?>
    <div class="sbq_logo">
      <div class="sbq_img">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
        </a>
      </div>
    </div>
    <?php endif; ?>
    <div class="sbq_header_login">
      <?php if (!$logged_in): ?>
      <div class="sbq_user_links">
        <a href="/user/login" class="log">登录</a>|<a href="/customer/register">注册</a>
      </div>
      <div class="sbq_user_pic">
        <a href="#"><img src="/<?php print $theme_path; ?>/image/default_avatar.png" width="50" height="50"  alt=""/></a>
      </div>
      <?php endif; ?>
      <?php if ($logged_in): ?>
      <?php
        global $user;
        $name = theme('username', array('account' => $user));
        $picture = theme('user_picture', array('account' =>$user));
        $user_link = '###';
        if($user->uid) {
          $user_link = '/user/'.$user->uid;
        }
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
<div class="siteindex" style="display:none;">
<h1><a href="/sites/index">伤不起文章资讯索引</a></h1>
</div>
<div class="sbq_qr_code">
  <div class="sbq_qr_code_inner"><a href="http://app.shangbq.com/update/CaseHistoryChart.v.1.87.apk"><img src="<?php print $theme_path; ?>/images/qr_code.png" width="100" height="140"  alt=""/></a></div>
</div>
<div class="body">
  <div class="main">
    <div class="sbq_home_menu">
      <ul class="sbq_patient">
        <li class="front-redblack color_06"><a href="###" onclick="alert('榜单沉淀中～敬请期待！');">
          <div class="sbq_img"></div>
          <div class="sbq_title">红黑榜</div>
          <div class="sbq_text">揭示医疗行业真相</div>
          </a></li>
        <li class="front-qa color_02"><a href="/questions/all">
          <div class="sbq_img"></div>
          <div class="sbq_title">问答</div>
          <div class="sbq_text">除了专业还要对症 </div>
          </a></li>
        <li class="front-event color_05"><a href="###" onclick="alert('精彩活动，即将开启,敬请期待！');">
          <div class="sbq_img"></div>
          <div class="sbq_title">活动</div>
          <div class="sbq_text">有你参与大不同</div>
          </a></li>
        <li class="front-legend color_07 half"><a href="/news/doctor_legend">
          <div class="sbq_img"></div>
          <div class="sbq_title">医界传奇 </div>
          </a></li>
        <li class="front-blacklist color_07 half"><a href="/news/hospital_blacklist">
          <div class="sbq_img"></div>
          <div class="sbq_title">曝光台</div>
          </a></li>
        <li class="front-activities color_07 half"><a href="/news/friend_activities">
          <div class="sbq_img"></div>
          <div class="sbq_title">爱心</div>
          </a></li>
        <li class="front-news color_07 half"><a href="/news/news">
          <div class="sbq_img"></div>
          <div class="sbq_title">资讯</div>
          </a></li>
      </ul>
      <ul class="sbq_doctor">

        <li class="front-relationship color_04">
          <?php if($user->uid) { ?>
            <a href="user/<?php echo $user->uid;?>/relationship" alt="人以群分确实必要">  
          <?php
          }else { ?>
            <a href="###" title="圈子" alt="人以群分确实必要" onclick="alert('请登录后使用!');">  
          <?php } ?>
          <div class="sbq_img"></div>
          <div class="sbq_title">圈子</div>
          <div class="sbq_text">人以群分确实必要</div>
          </a></li>
        <li class="front-doctor color_08">          
          <?php if($user->uid) { ?>
            <a href="user/<?php echo $user->uid;?>/relationship/default/doctor" alt="人以群分确实必要">  
          <?php
          }else { ?>
            <a href="###" title="医生馆" alt="专业医生的网上医院" onclick="alert('请登录后使用!');">  
          <?php } ?>
          <div class="sbq_img"></div>
          <div class="sbq_title">医生馆</div>
          <div class="sbq_text">专业医生的网上医院</div>
          </a></li>
      </ul>
      <ul class="sbq_focus">
        <li class="color_03 pic"><a href="###" onclick="alert('307免疫性流产治疗中心,敬请期待！');">
          <div class="sbq_img"><img src="/<?php print $theme_path; ?>/images/307.png" width="250" height="120"  alt=""/></div>
          <div class="sbq_title">307免疫性流产治疗中心</div>
          </a></li>
      </ul>
    </div>
  </div>
</div>
<div class="footer">
  <div class="footer_inner">
  <div class="sbq_about_link">
    <ul>
      <li><a href="/contact.html">联系我们</a></li>
      <li><a href="/services.html">注册服务条款</a></li>
      <li><a href="/copyright.html">免责声明</a></li>
      <li><a href="/join.html">加入我们</a></li>
      <li><a href="/about.html">关于我们</a></li>
    </ul>
  </div>
  <div class="sbq_copy">© 2014 伤不起 中国最真实的医疗评价平台(<a href="http://www.miitbeian.gov.cn" target="_bank"> 京ICP备13032461号-1</a>) </div>
  </div>
  <?php print render($page['footer']); ?>
</div> <!-- /#footer -->

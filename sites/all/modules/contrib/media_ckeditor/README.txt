CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Installation

INTRODUCTION
------------

Current Maintainers:

 * Devin Carlson <http://drupal.org/user/290182>

Media CKEditor provides a bridge between Media and the stand-alone CKEditor
module, allowing files to be embedded within a textarea using the media browser.

REQUIREMENTS
------------

Media CKEditor has two dependencies.

Contributed modules
 * CKEditor - The latest development release.
 * Media - 7.x-1.x.

INSTALLATION
------------

* Install Media CKEditor via the standard Drupal installation process:
  'http://drupal.org/node/895232'.
* Enable the 'Convert Media tags to markup' filter for the desired text formats
  from the Text Formats configuration page: '/admin/config/content/formats'.
* Enable the 'Plugin for inserting images from Drupal media module' Media
  CKEditor plugin for the desired text formats from the CKEditor configuration
  page: '/admin/config/content/ckeditor'.

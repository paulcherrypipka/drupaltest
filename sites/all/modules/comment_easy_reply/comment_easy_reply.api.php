<?php

/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * @defgroup comment_easy_reply_hooks Comment Easy Reply's hooks
 * @{
 * Hooks that can be implemented by other modules in order to extend Comment
 * Easy Reply module functionalities.
 */

/**
 * Create new tags to replace @#NUM in comments.
 *
 * This hook adds one or more tags to the list of available tags of Comment
 * Easy Reply module. Each new tag will be selectable through the module's
 * settings form.
 *
 * @return array
 *   An associative array of tags containing one sub-array for each tag.
 *   Possible attributes for each sub-array are:
 *   - label: The label of the tag. It will be showed on settings form.
 *     Required.
 *   - callback: A function to be called to get the tag to replace @#NUM with.
 *     Required.
 *   - title callback: A function to be called to get the tag to replace @#NUM
 *     with, specific for replacing inside comment subject. Required.
 *
 * @ingroup comment_easy_reply_hooks
 * @ingroup hooks
 */
function hook_comment_easy_reply_tags() {
  $tags = array();
  $tags['myfirsttag'] = array(
    'callback' => '_my_module_first_tag',
    'title callback' => '_my_module_first_tag_title',
    'label' => t('Display link as myfirsttag (Eg: @myfirsttag)'),
  );
  $tags['mysecondtag'] = array(
    'callback' => '_my_module_second_tag',
    'title callback' => '_my_module_second_tag_title',
    'label' => t('Display link as my#2tag (Eg: #my2ndtag)'),
  );
  return $tags;
}

/**
 * Alter tags added using hook_comment_easy_reply_tags().
 *
 * @param array &$tags
 *   The array of tags to be altered.
 *
 * @return array
 *   The array of tags, altered.
 *
 * @see hook_comment_easy_reply_tags()
 *
 * @ingroup comment_easy_reply_hooks
 * @ingroup hooks
 */
function hook_comment_easy_reply_tags_alter(&$tags) {
  if (isset($tags['module_to_be_altered'])) {
    $tags['module_to_be_altered']['label'] = t('My new custom label');
  }
  return $tags;
}

/**
 * @}
 */

/**
 * @defgroup comment_easy_reply_callbacks Comment Easy Reply's callbacks
 * @{
 * Examples of callbacks used in Comment Easy Reply module hooks.
 */

/**
 * Example callback used in hook_comment_easy_reply_tags().
 *
 * This callback creates a string used to replace a @#NUM tag.
 * The @#NUM tag is contained in a comment body and it refers to the comment
 * passed as an argument to the callback.
 * This example callback returns a string listing all the comment parents' ids.
 *
 * @param object &$comment
 *   The comment referred by the tag.
 *
 * @return string
 *   The string the @#NUM will be replaced with.
 *
 * @see hook_comment_easy_reply_tags()
 *
 * @ingroup comment_easy_reply_callbacks
 */
function _my_module_first_tag(&$comment) {
  $tag = '#parents:';
  $parents = _comment_easy_reply_comment_get_parents($comment);
  if (!empty($parents)) {
    $tag .= implode(',', array_keys($parents));
  }
  return $tag;
}

/**
 * Example callback used in hook_comment_easy_reply_tags().
 *
 * This callback creates a string used to replace a @#NUM tag.
 * The @#NUM tag is contained in a comment subject and it refers to the comment
 * passed as an argument to the callback.
 *
 * @param object &$comment
 *   The comment referred by the tag.
 *
 * @return string
 *   The string the @#NUM will be replaced with.
 *
 * @see hook_comment_easy_reply_tags()
 *
 * @ingroup comment_easy_reply_callbacks
 */
function _my_module_first_tag_title(&$comment) {
  return '#mytag:' . $comment->name;
}

/**
 * @}
 */

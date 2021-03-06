<?php

$plugin = array(
  'title' => t('Ding Facetbrowser'),
  'description' => t('Ding facetbrowser description'),
  'single' => TRUE,
  'content_types' => array('ding_facetbrowser'),
  'render callback' => 'ding_facetbrowser_content_type_render',
  'category' => t('Ting'),
  'render last' => TRUE, # Force the facetbrowser to be generated after the ting_search
);

/**
 * Callback function for the ctools content_type
 */
function ding_facetbrowser_content_type_render($subtype, $conf, $panel_args, $context) {
  $block_content          = FALSE;
  $content_in_facet       = FALSE;
  $executed_search_module = FALSE;
  $block                  = new stdClass();

  $block->module = 'ding_facetbrowser';
  $block->delta  = 'ding_facetbrowser';

  drupal_add_css(drupal_get_path('module', 'ding_facetbrowser') . '/css/facetbrowser.css');
  drupal_add_js(drupal_get_path('module', 'ding_facetbrowser') . '/js/facetbrowser.js');
  drupal_add_js(
    array('dingFacetBrowser' => array(
      'mainElement' => '.pane-ding-facetbrowser',
      'showCount' => 5)
    ), 'setting');

  // Invoke ding_facetbrowser() from executed search module
  $executed_search = menu_get_item();
  if (!empty($executed_search['page_arguments'])) {
    list($executed_search_module, ) = $executed_search['page_arguments'];
  }
  if (is_string($executed_search_module)) {
    $results = module_invoke($executed_search_module, 'ding_facetbrowser');
    if (is_object($results)) {
      foreach ($results->facets as $result) {
        if (count($result->terms) == TRUE) {
          $content_in_facet = TRUE;
          break;
        }
      }
      if ($content_in_facet === TRUE || $results->show_empty == TRUE) {
        $block_content = theme('facetbrowser', array($results->facets, (!empty($results->searchkey) ? $results->searchkey : NULL)));
      }
    }
    $block->title = t('Ding Facetbrowser');
    $block->content = $block_content;
    return $block;
  }
}

/**
 * Returns an edit form for settings
 */
function ding_facetbrowser_ding_facetbrowser_content_type_edit_form($form,&$form_state) {
  return $form;
}

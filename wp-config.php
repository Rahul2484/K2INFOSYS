<?php
/**
 * The base configurations of the WordPress.
 *
 * This file has the following configurations: MySQL settings, Table Prefix,
 * Secret Keys, and ABSPATH. You can find more information by visiting
 * {@link https://codex.wordpress.org/Editing_wp-config.php Editing wp-config.php}
 * Codex page. You can get the MySQL settings from your web host.
 *
 * This file is used by the wp-config.php creation script during the
 * installation. You don't have to use the web site, you can just copy this file
 * to "wp-config.php" and fill in the values.
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define('DB_NAME', 'wordpress');

/** MySQL database username */
define('DB_USER', 'root');

/** MySQL database password */
define('DB_PASSWORD', '');

/** MySQL hostname */
define('DB_HOST', 'localhost');

/** Database Charset to use in creating database tables. */
define('DB_CHARSET', 'utf8mb4');

/** The Database Collate type. Don't change this if in doubt. */
define('DB_COLLATE', '');


/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         ',E6ck)~%xA(-,BLqh+t~10ZbKu;oi*A@?U>U0LO_ PHjw_+_+RVuj(?oJr>:`g)]');
define('SECURE_AUTH_KEY',  'lE7x%u&FxK;[`O3oC4EJ)fT)O7R_LofL10VF#IBIAQiL1hQEtOj}Z0:Vf/W!}Dep');
define('LOGGED_IN_KEY',    ']XpPc8Y(FZ3Z@2JV2xlDBhP-o4hiC_q^ti,(OieRlE1~2/<mXgt!r8:buEiZ2[%c');
define('NONCE_KEY',        '=YgYtl3LqMYa(.*mWcu)&Q?a~7^!@J;C2kzY1F_<rjw?!6Xd&RnkA8Kwt*,/sBjZ');
define('AUTH_SALT',        'UH~R+ +w$-s4B~BjS&efx(hI$f4lJ`TNewGY{9!@0P@b%DBCreOpBamO~jd;#3=b');
define('SECURE_AUTH_SALT', '+Z<#Njb 73u8Fvtd1?8 _%Nd?#N%9*q-1{Ux22%2RQbOVm=|!6mm@g6@3gY.Um]Y');
define('LOGGED_IN_SALT',   '~){VbM[Zmt/[Z&t?Y~hp4EjV1<lm=>{/R8+tFU*{pkG/cx6fzXQQNN9~@MK2Sx1v');
define('NONCE_SALT',       '<zcdGL!::z9W:WW`<e(.nqDb[g^,rf4m,M4hlmd]R>k+OK@6M?#=xW7zq51~/G.&');

/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each a unique
 * prefix. Only numbers, letters, and underscores please!
 */
$table_prefix  = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 */
define('WP_DEBUG', false);

/* That's all, stop editing! Happy blogging. */

/** Absolute path to the WordPress directory. */
if ( !defined('ABSPATH') )
	define('ABSPATH', dirname(__FILE__) . '/');

/** Sets up WordPress vars and included files. */
require_once(ABSPATH . 'wp-settings.php');

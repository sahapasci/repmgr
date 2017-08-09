/*
 * repmgr-client.h
 * Copyright (c) 2ndQuadrant, 2010-2017
 */

#ifndef _REPMGR_CLIENT_H_
#define _REPMGR_CLIENT_H_

#include <getopt_long.h>
#include "log.h"



#define NO_ACTION			   0	/* Dummy default action */
#define PRIMARY_REGISTER	   1
#define PRIMARY_UNREGISTER	   2
#define STANDBY_REGISTER	   3
#define STANDBY_UNREGISTER	   4
#define STANDBY_CLONE		   5
#define STANDBY_PROMOTE		   6
#define STANDBY_FOLLOW		   7
#define STANDBY_SWITCHOVER	   8
#define BDR_REGISTER		   9
#define BDR_UNREGISTER		   10
#define NODE_STATUS			   11
#define NODE_CHECK			   12
#define NODE_SERVICE		   13
#define NODE_REJOIN            14
#define CLUSTER_SHOW		   15
#define CLUSTER_CLEANUP		   16
#define CLUSTER_MATRIX		   17
#define CLUSTER_CROSSCHECK	   18
#define CLUSTER_EVENT		   19

/* command line options without short versions */
#define OPT_HELP						   1001
#define OPT_CHECK_UPSTREAM_CONFIG		   1002
#define OPT_RECOVERY_MIN_APPLY_DELAY	   1003
#define OPT_COPY_EXTERNAL_CONFIG_FILES	   1004
#define OPT_CONFIG_ARCHIVE_DIR			   1005
#define OPT_PG_REWIND					   1006
#define OPT_PWPROMPT					   1007
#define OPT_CSV							   1008
#define OPT_NODE						   1009
#define OPT_NODE_ID					 	   1010
#define OPT_NODE_NAME				 	   1011
#define OPT_WITHOUT_BARMAN				   1012
#define OPT_NO_UPSTREAM_CONNECTION		   1013
#define OPT_REGISTER_WAIT				   1014
#define OPT_LOG_TO_FILE					   1015
#define OPT_UPSTREAM_CONNINFO			   1016
/* replaces --no-conninfo-password */
#define OPT_USE_RECOVERY_CONNINFO_PASSWORD 1017
#define OPT_REPLICATION_USER			   1018
#define OPT_EVENT						   1019
#define OPT_LIMIT						   1020
#define OPT_ALL							   1021
#define OPT_DRY_RUN						   1022
#define OPT_UPSTREAM_NODE_ID			   1023
#define OPT_ACTION                         1024
#define OPT_LIST_ACTIONS                   1025
#define OPT_CHECK                          1026
#define OPT_CHECKPOINT                     1027
#define OPT_IS_SHUTDOWN                    1028
#define OPT_ALWAYS_PROMOTE                 1029
#define OPT_FORCE_REWIND                   1030
#define OPT_NAGIOS                         1031
#define OPT_ARCHIVER                       1032
#define OPT_OPTFORMAT                      1033
#define OPT_REPLICATION_LAG                1034
#define OPT_CONFIG_FILES                   1035
/* deprecated since 3.3 */
#define OPT_DATA_DIR					    999
#define OPT_NO_CONNINFO_PASSWORD		    998


static struct option long_options[] =
{
/* general options */
	{"version", no_argument, NULL, 'V'},
	{"help", no_argument, NULL, OPT_HELP},

/* general configuration options */
	{"config-file", required_argument, NULL, 'f'},
	{"dry-run", no_argument, NULL, OPT_DRY_RUN},
	{"force", no_argument, NULL, 'F'},
	{"pg_bindir", required_argument, NULL, 'b'},
	{"wait", no_argument, NULL, 'W'},

/* connection options */
	{"dbname", required_argument, NULL, 'd'},
	{"host", required_argument, NULL, 'h'},
	{"port", required_argument, NULL, 'p'},
	{"remote-user", required_argument, NULL, 'R'},
	{"superuser", required_argument, NULL, 'S'},
	{"username", required_argument, NULL, 'U'},

/* general node options */
	{"pgdata", required_argument, NULL, 'D'},
	{"node-id", required_argument, NULL, OPT_NODE_ID},
	{"node-name", required_argument, NULL, OPT_NODE_NAME},

/* logging options */
	{"log-level", required_argument, NULL, 'L'},
	{"log-to-file", no_argument, NULL, OPT_LOG_TO_FILE},
	{"terse", no_argument, NULL, 't'},
	{"verbose", no_argument, NULL, 'v'},

/* output options */
	{"csv", no_argument, NULL, OPT_CSV},
	{"nagios", no_argument, NULL, OPT_NAGIOS},
	{"optformat", no_argument, NULL, OPT_OPTFORMAT},

/* "standby clone" options */
	{"copy-external-config-files", optional_argument, NULL, OPT_COPY_EXTERNAL_CONFIG_FILES},
	{"fast-checkpoint", no_argument, NULL, 'c'},
	{"wal-keep-segments", required_argument, NULL, 'w'},
	{"no-upstream-connection", no_argument, NULL, OPT_NO_UPSTREAM_CONNECTION},
	{"recovery-min-apply-delay", required_argument, NULL, OPT_RECOVERY_MIN_APPLY_DELAY},
	{"replication-user", required_argument, NULL, OPT_REPLICATION_USER},
	{"upstream-conninfo", required_argument, NULL, OPT_UPSTREAM_CONNINFO},
	{"upstream-node-id", required_argument, NULL, OPT_UPSTREAM_NODE_ID},
	{"use-recovery-conninfo-password", no_argument, NULL, OPT_USE_RECOVERY_CONNINFO_PASSWORD},
	{"without-barman", no_argument, NULL, OPT_WITHOUT_BARMAN},

/* "standby register" options */
	{"wait-sync", optional_argument, NULL, OPT_REGISTER_WAIT},

/* "standby switchover" options */
	{"remote-config-file", required_argument, NULL, 'C'},
	{"always-promote", no_argument, NULL, OPT_ALWAYS_PROMOTE },
	{"force-rewind", no_argument, NULL, OPT_FORCE_REWIND },

/* "node status" options */
	{"is-shutdown", no_argument, NULL, OPT_IS_SHUTDOWN },

/* "node check" options */
	{"archiver", no_argument, NULL, OPT_ARCHIVER },
	{"replication-lag", no_argument, NULL, OPT_REPLICATION_LAG },

/* "node join" options */
	{"config-files", required_argument, NULL, OPT_CONFIG_FILES },

/* "node service" options */
	{"action", required_argument, NULL, OPT_ACTION},
	{"check", no_argument, NULL, OPT_CHECK},
	{"list-actions", no_argument, NULL, OPT_LIST_ACTIONS},
	{"checkpoint", no_argument, NULL, OPT_CHECKPOINT},

/* "cluster event" options */
	{"all", no_argument, NULL, OPT_ALL },
	{"event", required_argument, NULL, OPT_EVENT },
	{"limit", required_argument, NULL, OPT_LIMIT },

/* Following options for internal use */
	{"config-archive-dir", required_argument, NULL, OPT_CONFIG_ARCHIVE_DIR},

/* deprecated */
	{"no-conninfo-password", no_argument, NULL, OPT_NO_CONNINFO_PASSWORD},
	/* legacy alias for -D/--pgdata*/
	{"data-dir", required_argument, NULL, OPT_DATA_DIR},
	/* --node-id */
	{"node", required_argument, NULL, OPT_NODE},


/* not yet handled */
	{"keep-history", required_argument, NULL, 'k'},
	{"mode", required_argument, NULL, 'm'},
	{"check-upstream-config", no_argument, NULL, OPT_CHECK_UPSTREAM_CONFIG},
	{"pg_rewind", optional_argument, NULL, OPT_PG_REWIND},
	{"pwprompt", optional_argument, NULL, OPT_PWPROMPT},


	{NULL, 0, NULL, 0}
};



static void do_help(void);



static const char *action_name(const int action);

static void check_cli_parameters(const int action);

static void write_primary_conninfo(char *line, t_conninfo_param_list *param_list);
static bool write_recovery_file_line(FILE *recovery_file, char *recovery_file_path, char *line);

#endif /* _REPMGR_CLIENT_H_ */

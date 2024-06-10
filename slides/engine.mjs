// import { Marp } from '@marp-team/marp-core'
// import highlightLines from 'markdown-it-highlight-lines'

// export default (opts) => new Marp(opts)
//     .use(highlightLines);

import { Marp } from '@marp-team/marp-core'
import highlightLines from 'markdown-it-highlight-lines'
import include from 'markdown-it-include'

export default (opts) => new Marp(opts)
    .use(highlightLines)
    .use(include, {
        root: '.',  // Set the root directory for include files
        //includeRe: /^\s*#include:\s*(.+?)\s*$/
    });

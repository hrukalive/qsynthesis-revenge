export class DiffScopeHandle {

    constructor(internal) {

        this._internal = internal;

        this.dialogSystem = {
            form: (title, widgets, listener) => {
                return this._internal.form(title, widgets, listener ? (rawHandle) => {
                    listener(widgets.map((v, i) => {
                        let handle = {};
                        Object.defineProperties(handle, {
                            value: {
                                get: () => rawHandle.value(i),
                            },
                            visible: {
                                get: () => rawHandle.visible(i),
                                set: v => { rawHandle.setVisible(i, v) },
                            },
                            disabled: {
                                get: () => rawHandle.disabled(i),
                                set: v => { rawHandle.setDisabled(i, v) },
                            },
                            label: {
                                get: () => rawHandle.label(i),
                                set: v => { rawHandle.setLabel(i, v) },
                            },
                        });
                        return handle;
                    }));
                } : undefined);
            },
            alert: (title, message) => {
                this._internal.infoMsgBox(title, message);
            },
            confirm: (title, message, defaultButton = 'Yes') => {
                return this._internal.questionMsgBox(title, message, defaultButton);
            },
            prompt: (title, message, defaultValue) => {
                let res =  this._internal.form(
                    title,
                    [{ type: 'TextBox', label: message, defaultValue }],
                );
                if(res.result == 'Ok') {
                    return res.form[0];
                } else {
                    return null;
                }
            },
            msgBox: (title, message, icon = '', buttons = ['Ok'], defaultButton = '') => {
                return this._internal.msgBox(title, message, icon, buttons, defaultButton);
            }
        };

        this.actionSystem = {};

        this.project = {};

        this.utils = {};
    }

}
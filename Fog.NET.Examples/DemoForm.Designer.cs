namespace Fog.NET.Examples
{
    partial class DemoForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.btnClear = new System.Windows.Forms.Button();
            this.btnDrawLines = new System.Windows.Forms.Button();
            this.btnDrawText = new System.Windows.Forms.Button();
            this.btnDrawSvg = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(15, 16);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(361, 321);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(397, 16);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(75, 23);
            this.btnClear.TabIndex = 1;
            this.btnClear.Text = "Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // btnDrawLines
            // 
            this.btnDrawLines.Location = new System.Drawing.Point(397, 55);
            this.btnDrawLines.Name = "btnDrawLines";
            this.btnDrawLines.Size = new System.Drawing.Size(75, 23);
            this.btnDrawLines.TabIndex = 2;
            this.btnDrawLines.Text = "Draw Lines";
            this.btnDrawLines.UseVisualStyleBackColor = true;
            this.btnDrawLines.Click += new System.EventHandler(this.btnDrawLines_Click);
            // 
            // btnDrawText
            // 
            this.btnDrawText.Location = new System.Drawing.Point(397, 97);
            this.btnDrawText.Name = "btnDrawText";
            this.btnDrawText.Size = new System.Drawing.Size(75, 23);
            this.btnDrawText.TabIndex = 3;
            this.btnDrawText.Text = "Draw Text";
            this.btnDrawText.UseVisualStyleBackColor = true;
            this.btnDrawText.Click += new System.EventHandler(this.btnDrawText_Click);
            // 
            // btnDrawSvg
            // 
            this.btnDrawSvg.Location = new System.Drawing.Point(397, 140);
            this.btnDrawSvg.Name = "btnDrawSvg";
            this.btnDrawSvg.Size = new System.Drawing.Size(75, 23);
            this.btnDrawSvg.TabIndex = 4;
            this.btnDrawSvg.Text = "Draw Svg...";
            this.btnDrawSvg.UseVisualStyleBackColor = true;
            this.btnDrawSvg.Click += new System.EventHandler(this.btnDrawSvg_Click);
            // 
            // DemoForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(583, 349);
            this.Controls.Add(this.btnDrawSvg);
            this.Controls.Add(this.btnDrawText);
            this.Controls.Add(this.btnDrawLines);
            this.Controls.Add(this.btnClear);
            this.Controls.Add(this.pictureBox1);
            this.Name = "DemoForm";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Button btnDrawLines;
        private System.Windows.Forms.Button btnDrawText;
        private System.Windows.Forms.Button btnDrawSvg;
    }
}


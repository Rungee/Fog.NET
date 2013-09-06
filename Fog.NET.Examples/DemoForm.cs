/******************************************************************************
*
* Name:     DemoForm.cpp
* Project:  Fog-Framework (Copyright (c) 2006-2011, Petr Kobalicek <kobalicek.petr@gmail.com>) C++/CLI Interface
* Author:   Maxim Rylov
*
******************************************************************************
* The MIT License (MIT)
*
* Copyright (C) 2013, Maxim Rylov
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*****************************************************************************/

using System;
using System.Drawing;
using System.Windows.Forms;

using FogNET;

using Image = FogNET.Image;

namespace Fog.NET.Examples
{
    public partial class DemoForm : Form
    {
        private Bitmap m_bitmap;
        private Painter m_painter;
        private Image m_image;

        public DemoForm()
        {
            InitializeComponent();

            m_bitmap = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            m_image = new Image(m_bitmap);
            m_painter = new Painter(m_image);

            pictureBox1.Image = m_bitmap;

            btnClear_Click(this, null);
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            m_painter.SetSource(Color.White);
            m_painter.FillAll();

            UpdatePictureBox();
        }

        private void UpdatePictureBox()
        {
            pictureBox1.Image = m_bitmap;
            pictureBox1.Refresh();
        }

        private void btnDrawLines_Click(object sender, EventArgs e)
        {
            m_painter.SetSource(Color.Blue);
            m_painter.DrawLine(20, 20, 100, 160);

            UpdatePictureBox();
        }

        private void btnDrawText_Click(object sender, EventArgs e)
        {
            m_painter.SetSource(Color.Red);

            using (PathF path = new PathF())
            {
                using (FogNET.Font font = new FogNET.Font("Tahoma", 12))
                {
                    path.AddString("Hello Foggy :)", font, new PointF(120, 50));
                }

                m_painter.FillPath(path);
            }

            UpdatePictureBox();
        }

        private void btnDrawSvg_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog ofd = new OpenFileDialog())
            {
                ofd.Filter = "(*.svg)|*.svg";
                if (ofd.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    //System.IO.FileStream fs = System.IO.File.OpenRead(ofd.FileName);
                    SvgDocument doc = SvgDocument.FromFile(ofd.FileName);
                    //SvgDocument doc = SvgDocument.FromStream(fs);
                    doc.Render(m_painter);
                    doc.Dispose();

                    UpdatePictureBox();
                }
            }
        }
    }
}
